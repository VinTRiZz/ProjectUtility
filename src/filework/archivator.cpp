#include "archivator.h"

#include <QFileInfo>
#include <QDir>

#include <thread>
#include <QProcess>

#include <QVector>
#include <QDebug>

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
    QProcess packProcess;
    std::thread * pPackThread {nullptr};
    ArchiveDirectory mainArchiveDir;

    Impl()
    {
        mainArchiveDir.archivePath = "./archiveTemp";
    }

    void poll()
    {
        if (pPackThread)
        {
            if (pPackThread->joinable())
                pPackThread->join();
            delete pPackThread;
            pPackThread = nullptr;
        }
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
            qDebug() << "[ARCHIVATOR] \033[33mIgnoring\033[0m file:" << fileName;
            return false;
        }

        return true;
    }

    void archive()
    {
        const QString mkdirCommand = "mkdir " + mainArchiveDir.archivePath + " &> /dev/null";
        system(mkdirCommand.toUtf8().data());
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
                currentArchiveDir.children.push_back(dir);
                searchRecursive( QDir(entryPath), currentArchiveDir.children[currentArchiveDir.children.size() - 1] );

            } else if (mustPackThisFile(entry))
            {
                currentArchiveDir.filesToPack << entryPath;
            }
        }
    }

    void searchForProjectFiles(const QDir & currentDir, ArchiveDirectory & currentArchiveDir)
    {
        QStringList entries = currentDir.entryList();

        // Ignore useless entries
        entries.removeOne(".");
        entries.removeOne("..");
        entries.removeOne("BIN");
        entries.removeOne("BUILD");

        QString entryPath;
        for (QString & entry : entries)
        {
            entryPath = currentDir.absoluteFilePath(entry);
            if ( QFileInfo( entryPath ).isDir() )
            {
                ArchiveDirectory dir;
                dir.dirName = entry;
                currentArchiveDir.children.push_back(dir);
                searchRecursive( QDir(entryPath), currentArchiveDir.children[currentArchiveDir.children.size() - 1] );

            } else if (mustPackThisFile(entry))
            {
                currentArchiveDir.filesToPack << entryPath;
            }
        }
    }
};

Archivator::Archivator() :
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

    m_pImpl->searchForProjectFiles(projectDir, m_pImpl->mainArchiveDir);

    return true;
}

bool Archivator::archive()
{
    m_pImpl->poll();

    // TODO: Setup process
}

void Archivator::poll()
{
    m_pImpl->poll();
}
