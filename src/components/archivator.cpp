#include "archivator.h"

#include <QFileInfo>
#include <QDir>

#include <thread>
#include <QProcess>

#include <QVector>
#include <QDebug>

#include <QThread>

using namespace ProjectUtility;

namespace ProjectUtility
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
        mainArchiveDir.dirName = m_utilClass.projectConfiguration().strSettings["Program default directory"] + "/Projects";
        mainArchiveDir.archivePath = m_utilClass.projectConfiguration().strSettings["Program default directory"] + "/Projects";
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
                    m_utilClass.logChannel() << "[ARCHIVATOR] \033[33mSkipped\033[0m directory:" << entry;

            } else if (currentArchiveDir.archivePath.contains("/include/"))
            {
                currentArchiveDir.filesToPack << entryPath;
            }
            else if (mustPackThisFile(entry))
            {
                currentArchiveDir.filesToPack << entryPath;
            } else
            {
                m_utilClass.logChannel() << "[ARCHIVATOR] \033[33mSkipped\033[0m file:" << entry;
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
    d {new Impl(utilClass)}
{

}

Archivator::~Archivator()
{
    d->poll();
}

bool Archivator::addFile(const QString & path)
{
    d->poll();

    QFileInfo fileTester(path);

    if ((!fileTester.exists()) || (fileTester.isDir()))
        return false;

    bool exist = false;
    const QString dirName = fileTester.absoluteDir().dirName();
    for (const ArchiveDirectory & child : d->mainArchiveDir.children)
    {
        if (child.dirName == dirName)
        {
            exist = true;
            break;
        }
    }

    if (!exist)
        d->mainArchiveDir.filesToPack << path;

    return true;
}

bool Archivator::addProject(const QString &projectDirPath)
{
    d->poll();

    QFileInfo fileTester(projectDirPath);

    if ((!fileTester.exists()) || (!fileTester.isDir()))
    {
        d->m_utilClass.logChannel() << "[ARCHIVATOR] Project not added";
        return false;
    }

    QDir projectDir(projectDirPath);

    ArchiveDirectory projectArchiveDir;
    projectArchiveDir.dirName = fileTester.baseName();
    projectArchiveDir.archivePath = d->mainArchiveDir.archivePath + "/" + projectArchiveDir.dirName;

    d->searchRecursive(projectDir, projectArchiveDir);

    d->mainArchiveDir.children.push_back(projectArchiveDir);

    return true;
}

void Archivator::archive(const QString & resultPath)
{
    if (resultPath.size() < 1)
        return;

    d->poll();

    d->processThread = QThread::create(
        [this, resultPath]()
        {
            const QString basePathInTmp = "./Projects";

            QStringList dirArgs;
            dirArgs << basePathInTmp;

            // Create temporary directory for them
            if (!d->m_utilClass.invoke("mkdir", dirArgs, d->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                d->m_utilClass.logChannel() << "[ARCHIVATOR] Error: Temporary directory not created";
                emit this->archiveComplete(false);
                return;
            }

            d->setupDirsRecursive(d->mainArchiveDir);
            d->copyFilesRecursive(d->mainArchiveDir);

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
            d->m_utilClass.logChannel() << "[ARCHIVATOR] Archivator command: [" << "zip" << zipArgs.join(" ") << "]";

            if (d->m_utilClass.invoke("zip", zipArgs, d->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                d->m_utilClass.logChannel() << "[ARCHIVATOR] Archive created:" << resultPath;
                emit this->archiveComplete(true);
            }
            else
                emit this->archiveComplete(false);

            dirArgs << "-R";
            d->m_utilClass.invoke("rm", dirArgs, d->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]);
        }
    );

    d->processThread->start();
}

void Archivator::poll()
{
    d->poll();
}

void Archivator::clear()
{
    d->mainArchiveDir.children.clear();
    d->mainArchiveDir.filesToPack.clear();
}

void Archivator::archive(const QString &projectDirPath, const QString &resultPath)
{
    if (resultPath.size() < 1)
        return;

    d->poll();

    d->processThread = QThread::create(
        [this, projectDirPath, resultPath]()
        {
            // Search for project files
            QDir projectDir(projectDirPath);

            const QString basePathInTmp = "./Projects";

            ArchiveDirectory projectArhiveDir;
            projectArhiveDir.dirName = projectDir.dirName();
            projectArhiveDir.archivePath = basePathInTmp;

            d->searchRecursive(QDir(projectDirPath), projectArhiveDir);

            QStringList dirArgs;
            dirArgs << basePathInTmp;

            // Create temporary directory for them
            if (!d->m_utilClass.invoke("mkdir", dirArgs, d->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                d->m_utilClass.logChannel() << "[ARCHIVATOR] Error: directory not created";
                emit this->archiveComplete(false);
                return;
            }

            d->setupDirsRecursive(projectArhiveDir);
            d->copyFilesRecursive(projectArhiveDir);

            const QString zipRecursivelyArg = "-r", zipUpdateExistArg = "-u";

            // Archive them
            QStringList zipArgs;
            zipArgs << zipRecursivelyArg
                    << zipUpdateExistArg
                    << resultPath
                    << basePathInTmp
            ;
            d->m_utilClass.logChannel() << "[ARCHIVATOR] Archivator command: [" << "zip" << zipArgs.join(" ") << "]";

            if (d->m_utilClass.invoke("zip", zipArgs, d->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]))
            {
                d->m_utilClass.logChannel() << "[ARCHIVATOR] Archive created:" << resultPath;
                emit this->archiveComplete(true);
            }
            else
                emit this->archiveComplete(false);

            dirArgs << "-R";
            d->m_utilClass.invoke("rm", dirArgs, d->m_utilClass.projectConfiguration().intSettings["ZIP program timeout"]);
        }
    );

    d->processThread->start();
}
