#include "archivator.h"

#include <QFileInfo>
#include <QDir>

#include <thread>
#include <QProcess>

#include <QVector>
#include <QDebug>

#include <QThread>

using namespace DependsSearcher;

namespace DependsSearcher
{

struct ArchiveDirectory
{
    QString archivePath;
    QString dirName;
    QStringList filesToPack;
    QVector<ArchiveDirectory> children;
};

}

struct Archivator::Impl
{
    UtilFunctionClass & m_utilClass;

    ArchiveDirectory mainArchiveDir;
    QThread * processThread {nullptr};

    Impl(UtilFunctionClass & utilClass) :
        m_utilClass{utilClass}
    {
        mainArchiveDir.dirName = "Projects";
        mainArchiveDir.archivePath = "Projects";
    }

    void poll()
    {
        if (!processThread)
            return;

        if (processThread->isFinished())
            return;

        if (processThread->isRunning())
        {
            if (!processThread->wait(m_utilClass.projectConfiguration().intSettings["Archive thread timeout"]))
                processThread->exit(1);
        }

        processThread->deleteLater();
        processThread = nullptr;
    }

    bool mustPackThisFile(const QString & fileName)
    {
        if (fileName.contains("/")) // Input must be only names
            return false;

        if (fileName.contains(QRegExp("moc_[A-Za-z0-9]+\\.h"))    ||
            fileName.contains(QRegExp("moc_[A-Za-z0-9]+\\.cpp"))  ||
            fileName.contains(QRegExp("[A-Za-z0-9]+\\.pro.user")) ||
            fileName.contains(QRegExp("[A-Za-z0-9]+\\.o")) ||
            // fileName.contains(QRegExp("ui_[A-Za-z0-9]+\\.h"))     ||
            (fileName == "Makefile")                              // ||
//            (
//                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.h"))   &&
//                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.cpp")) &&
//                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.ui"))  &&
//                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.pro")) &&
//                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.pri"))
//            )
        )
        {
            return false;
        }

        return true;
    }

    void searchRecursive(const QDir & currentDir, ArchiveDirectory & currentArchiveDir)
    {
        QStringList entries = currentDir.entryList();

        // Ignore useless entries
        entries.removeOne(".");
        entries.removeOne("..");

        QString entryPath;
        for (QString & entry : entries)
        {
            entryPath = currentDir.absoluteFilePath(entry);
            if ( QFileInfo( entryPath ).isDir() )
            {
                ArchiveDirectory dir;
                dir.dirName = entry;
                dir.archivePath = currentArchiveDir.archivePath + "/" + entry;
                searchRecursive( QDir(entryPath), dir );
                if ((dir.children.size() > 0) || (dir.filesToPack.size() > 0))
                    currentArchiveDir.children.push_back(dir);
                else
                    qDebug() << "[ARCHIVATOR] \033[33mSkipped\033[0m directory:" << entry;

            } else if (currentArchiveDir.archivePath.contains("/include/"))
            {
                currentArchiveDir.filesToPack << entryPath;
            }
            else if (mustPackThisFile(entry))
            {
                currentArchiveDir.filesToPack << entryPath;
            } else
            {
                qDebug() << "[ARCHIVATOR] \033[33mSkipped\033[0m file:" << entry;
            }
        }
    }

    void setupDirsRecursive(ArchiveDirectory & currentArchiveDir)
    {
        for (ArchiveDirectory & dir : currentArchiveDir.children)
        {
            const QString mkdirCommand = QString("mkdir %1 &> /dev/null").arg(dir.archivePath);
            system(mkdirCommand.toUtf8().data());
            setupDirsRecursive( dir );
        }
    }

    void copyFilesRecursive(ArchiveDirectory & currentArchiveDir)
    {
        for (QString & path : currentArchiveDir.filesToPack)
            QFile::copy(path, currentArchiveDir.archivePath + "/" + QFileInfo(path).fileName());

        for (ArchiveDirectory & dir : currentArchiveDir.children)
            copyFilesRecursive( dir );
    }
};

Archivator::Archivator(UtilFunctionClass & utilClass, QObject * parent) :
    QObject(parent),
    m_pImpl {new Impl(utilClass)}
{

}

Archivator::~Archivator()
{
    m_pImpl->poll();
}

bool Archivator::addFile(const QString & path)
{
    m_pImpl->poll();

    QFileInfo fileTester(path);

    if ((!fileTester.exists()) || (fileTester.isDir()))
        return false;

    bool exist = false;
    const QString dirName = fileTester.absoluteDir().dirName();
    for (const ArchiveDirectory & child : m_pImpl->mainArchiveDir.children)
    {
        if (child.dirName == dirName)
        {
            exist = true;
            break;
        }
    }

    if (!exist)
        m_pImpl->mainArchiveDir.filesToPack << path;

    return true;
}

bool Archivator::addProject(const QString &projectDirPath)
{
    m_pImpl->poll();

    QFileInfo fileTester(projectDirPath);

    if ((!fileTester.exists()) || (!fileTester.isDir()))
    {
        qDebug() << "[ARCHIVATOR] Project not added";
        return false;
    }

    QDir projectDir(projectDirPath);

    ArchiveDirectory projectArchiveDir;
    projectArchiveDir.dirName = fileTester.baseName();
    projectArchiveDir.archivePath = m_pImpl->mainArchiveDir.archivePath + "/" + projectArchiveDir.dirName;

    m_pImpl->searchRecursive(projectDir, projectArchiveDir);

    m_pImpl->mainArchiveDir.children.push_back(projectArchiveDir);

    return true;
}

void Archivator::archive(const QString & resultPath)
{
    if (resultPath.size() < 1)
        return;

    m_pImpl->poll();

    m_pImpl->processThread = QThread::create(
        [this, resultPath]()
        {
            const QString basePathInTmp = "./Projects";

            QStringList dirArgs;
            dirArgs << basePathInTmp;

            // Create temporary directory for them
            if (!m_pImpl->m_utilClass.invoke("mkdir", dirArgs, m_pImpl->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                qDebug() << "[ARCHIVATOR] Error: Temporary directory not created";
                emit this->archiveComplete(false);
                return;
            }

            m_pImpl->setupDirsRecursive(m_pImpl->mainArchiveDir);
            m_pImpl->copyFilesRecursive(m_pImpl->mainArchiveDir);

            // Archive them
            QProcess packProcess;
            packProcess.setProgram("zip");

            QStringList zipArgs;
            const QString zipRecursivelyArg = "-r", zipUpdateExistArg = "-u";
            zipArgs << zipRecursivelyArg
                    << zipUpdateExistArg
                    << resultPath
                    << basePathInTmp
            ;
            qDebug() << "[ARCHIVATOR] Archivator command: [" << "zip" << zipArgs.join(" ") << "]";

            if (m_pImpl->m_utilClass.invoke("zip", zipArgs, m_pImpl->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                qDebug() << "[ARCHIVATOR] Archive created:" << resultPath;
                emit this->archiveComplete(true);
            }
            else
                emit this->archiveComplete(false);

            dirArgs << "-R";
            m_pImpl->m_utilClass.invoke("rm", dirArgs, m_pImpl->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]);
        }
    );

    m_pImpl->processThread->start();
}

void Archivator::poll()
{
    m_pImpl->poll();
}

void Archivator::clear()
{
    m_pImpl->mainArchiveDir.children.clear();
    m_pImpl->mainArchiveDir.filesToPack.clear();
}

void Archivator::archive(const QString &projectDirPath, const QString &resultPath)
{
    if (resultPath.size() < 1)
        return;

    m_pImpl->poll();

    m_pImpl->processThread = QThread::create(
        [this, projectDirPath, resultPath]()
        {
            // Search for project files
            QDir projectDir(projectDirPath);

            const QString basePathInTmp = "./Projects";

            ArchiveDirectory projectArhiveDir;
            projectArhiveDir.dirName = projectDir.dirName();
            projectArhiveDir.archivePath = basePathInTmp;

            m_pImpl->searchRecursive(QDir(projectDirPath), projectArhiveDir);

            QStringList dirArgs;
            dirArgs << basePathInTmp;

            // Create temporary directory for them
            if (!m_pImpl->m_utilClass.invoke("mkdir", dirArgs, m_pImpl->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                qDebug() << "[ARCHIVATOR] Error: directory not created";
                emit this->archiveComplete(false);
                return;
            }

            m_pImpl->setupDirsRecursive(projectArhiveDir);
            m_pImpl->copyFilesRecursive(projectArhiveDir);

            const QString zipRecursivelyArg = "-r", zipUpdateExistArg = "-u";

            // Archive them
            QStringList zipArgs;
            zipArgs << zipRecursivelyArg
                    << zipUpdateExistArg
                    << resultPath
                    << basePathInTmp
            ;
            qDebug() << "[ARCHIVATOR] Archivator command: [" << "zip" << zipArgs.join(" ") << "]";

            if (m_pImpl->m_utilClass.invoke("zip", zipArgs, m_pImpl->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                qDebug() << "[ARCHIVATOR] Archive created:" << resultPath;
                emit this->archiveComplete(true);
            }
            else
                emit this->archiveComplete(false);

            dirArgs << "-R";
            m_pImpl->m_utilClass.invoke("rm", dirArgs, m_pImpl->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]);
        }
    );

    m_pImpl->processThread->start();
}
