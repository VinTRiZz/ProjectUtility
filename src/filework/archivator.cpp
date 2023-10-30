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
        {
            return;
        }

        if (processThread->isFinished())
        {
            return;
        }

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

    void copyRecursive(const QDir & currentDir, ArchiveDirectory & currentArchiveDir)
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
                const QString mkdirCommand = QString("mkdir %1 &> /dev/null").arg(currentArchiveDir.archivePath);
                system(mkdirCommand.toUtf8().data());
                copyRecursive( QDir(entryPath), currentArchiveDir.children[currentArchiveDir.children.size() - 1] );

            } else if (mustPackThisFile(entry))
            {
                currentArchiveDir.filesToPack << entryPath;
            }
        }
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

    m_pImpl->searchRecursive(projectDir, m_pImpl->mainArchiveDir);

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

            const QString mkdirCommand = "mkdir " + m_pImpl->mainArchiveDir.dirName + " &> /dev/null";
            system(mkdirCommand.toUtf8().data());

            if (!QFileInfo(m_pImpl->mainArchiveDir.dirName).exists())
            {
                qDebug() << "[ARCHIVATOR] Error: directory not created";
                emit this->archiveComplete();
                return;
            }

            QProcess packProcess;
            packProcess.setProgram("zip");

            QStringList zipArgs;
            const QString zipRecursivelyArg = "-r", zipUpdateExistArg = "-u";
            zipArgs << zipRecursivelyArg
                    << zipUpdateExistArg
                    << resultPath
                    << m_pImpl->mainArchiveDir.dirName
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
                    m_pImpl->isArchived = true;
                }
                else
                {
                    qDebug() << "[ARCHIVATOR] Error creating archive: [\033[32mSTDOUT\033[0m" << packProcess.readAllStandardOutput() << "] | [\033[31mSTDERR\033[0m" << packProcess.readAllStandardOutput() << "]";
                }
            }
            else
            {
                qDebug() << "[ARCHIVATOR] Archive command start error";
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

            ArchiveDirectory projectArhiveDir;
            projectArhiveDir.dirName = projectDir.dirName();
            projectArhiveDir.archivePath = projectDir.dirName();

            m_pImpl->searchRecursive(QDir(projectDirPath), projectArhiveDir);

            // Create temporary directory for them
            const QString mkdirCommand = "mkdir " + projectArhiveDir.dirName + " &> /dev/null";
            system(mkdirCommand.toUtf8().data());

            if (!QFileInfo(projectArhiveDir.dirName).exists())
            {
                qDebug() << "[ARCHIVATOR] Error: directory not created";
                emit this->archiveComplete();
                return;
            }

            // Archive them
            QProcess packProcess;
            packProcess.setProgram("zip");

            QStringList zipArgs;
            const QString zipRecursivelyArg = "-r", zipUpdateExistArg = "-u";
            zipArgs << zipRecursivelyArg
                    << zipUpdateExistArg
                    << resultPath
                    << projectArhiveDir.dirName
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
                    m_pImpl->isArchived = true;
                }
                else
                {
                    qDebug() << "[ARCHIVATOR] Error creating archive: [\033[32mSTDOUT\033[0m" << packProcess.readAllStandardOutput() << "] | [\033[31mSTDERR\033[0m" << packProcess.readAllStandardOutput() << "]";
                }
            }
            else
            {
                qDebug() << "[ARCHIVATOR] Archive command start error";
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
