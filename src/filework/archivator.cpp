#include "archivator.h"

#include <QFileInfo>
#include <QDir>

#include <thread>
#include <QProcess>

#include <QVector>
#include <QDebug>

#include <QThread>

// Timeout of thread in poll() function
#define PROCESS_THREAD_TIMEOUT 60000

// Timeout for archiving (1h)
#define ZIP_PROCESS_TIMEOUT 3600000

using namespace FileWork;

namespace FileWork
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
    ArchiveDirectory mainArchiveDir;
    QThread * processThread {nullptr};
    bool isArchived {false};

    Impl()
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
            processThread->wait(PROCESS_THREAD_TIMEOUT);
        }

        processThread->deleteLater();
        processThread = nullptr;
    }

    bool mustPackThisFile(const QString & fileName)
    {
        if (fileName.contains("/")) // Input must be only names
            return false;

        if (fileName.contains(QRegExp("ui_[A-Za-z0-9]+\\.h"))     ||
            fileName.contains(QRegExp("moc_[A-Za-z0-9]+\\.h"))    ||
            fileName.contains(QRegExp("moc_[A-Za-z0-9]+\\.cpp"))  ||
            fileName.contains(QRegExp("[A-Za-z0-9]+\\.pro.user")) ||
            (fileName == "Makefile")                              ||
            (
                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.h"))   &&
                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.cpp")) &&
                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.ui"))  &&
                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.pro")) &&
                !fileName.contains(QRegExp("[A-Za-z0-9]+\\.pri"))
            )
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

Archivator::Archivator(QObject * parent) :
    QObject(parent),
    m_pImpl {new Impl}
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
            m_pImpl->isArchived = false;

            const QString basePathInTmp = QString("./%1").arg(m_pImpl->mainArchiveDir.dirName);

            // Create temporary directory for them
            const QString mkdirCommand = "mkdir " + basePathInTmp + " &> /dev/null";
            system(mkdirCommand.toUtf8().data());

            if (!QFileInfo(basePathInTmp).exists())
            {
                qDebug() << "[ARCHIVATOR] Error: directory not created";
                return;
            }

            QString mkProjectDirCommand;
            for (auto child : m_pImpl->mainArchiveDir.children)
            {
                mkProjectDirCommand = QString("mkdir %1/%2 &> /dev/null").arg(m_pImpl->mainArchiveDir.archivePath, child.dirName);
                system(mkdirCommand.toUtf8().data());
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

            packProcess.setArguments(zipArgs);

            packProcess.start();

            if (packProcess.waitForStarted(ZIP_PROCESS_TIMEOUT))
            {
                if (!packProcess.waitForFinished(ZIP_PROCESS_TIMEOUT))
                {
                    packProcess.kill();
                }
                if (!packProcess.exitCode())
                {
                    qDebug() << "[ARCHIVATOR] Archive created:" << resultPath;
                    const QString rmCommand = QString("rm %1 -R").arg(basePathInTmp);
                    system(rmCommand.toUtf8().data());
                    m_pImpl->isArchived = true;
                }
                else
                {
                    qDebug() << "[ARCHIVATOR] Error creating archive: [\033[32mSTDOUT\033[0m" << packProcess.readAllStandardOutput() << "] | [\033[31mSTDERR\033[0m" << packProcess.readAllStandardOutput() << "]";
                }
            }
            emit this->archiveComplete();
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
            m_pImpl->isArchived = false;

            // Search for project files
            QDir projectDir(projectDirPath);

            const QString basePathInTmp = QString("./%1").arg(projectDir.dirName());

            ArchiveDirectory projectArhiveDir;
            projectArhiveDir.dirName = projectDir.dirName();
            projectArhiveDir.archivePath = basePathInTmp;

            m_pImpl->searchRecursive(QDir(projectDirPath), projectArhiveDir);

            // Create temporary directory for them
            const QString mkdirCommand = "mkdir " + basePathInTmp + " &> /dev/null";
            system(mkdirCommand.toUtf8().data());

            if (!QFileInfo(basePathInTmp).exists())
            {
                qDebug() << "[ARCHIVATOR] Error: directory not created";
                return;
            }

            m_pImpl->setupDirsRecursive(projectArhiveDir);
            m_pImpl->copyFilesRecursive(projectArhiveDir);

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

            packProcess.setArguments(zipArgs);

            packProcess.start();

            if (packProcess.waitForStarted(ZIP_PROCESS_TIMEOUT))
            {
                if (!packProcess.waitForFinished(ZIP_PROCESS_TIMEOUT))
                {
                    packProcess.kill();
                }
                if (!packProcess.exitCode())
                {
                    qDebug() << "[ARCHIVATOR] Archive created:" << resultPath;
                    const QString rmCommand = QString("rm %1 -R").arg(basePathInTmp);
                    system(rmCommand.toUtf8().data());
                    m_pImpl->isArchived = true;
                }
                else
                {
                    qDebug() << "[ARCHIVATOR] Error creating archive: [\033[32mSTDOUT\033[0m" << packProcess.readAllStandardOutput() << "] | [\033[31mSTDERR\033[0m" << packProcess.readAllStandardOutput() << "]";
                }
            }
            emit this->archiveComplete();
        }
    );

    m_pImpl->processThread->start();
}

bool Archivator::archived() const
{
    return m_pImpl->isArchived;
}
