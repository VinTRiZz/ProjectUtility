#include "projectdirectoryfileinterface.h"

#include "filesearcher.h"
#include "backupmanager.h"
#include "dependsworker.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

#include <thread>

using namespace FileWork;

struct ProjectDirectoryFileInterface::Impl
{
    QVector<Project> apps;
    QVector<Project> libs;

    QString currentBasePath;

    FileSearcher m_searcher{ apps, libs };
    DependsWorker m_dependsWorker {apps, libs };

    BackupManager m_backupManager;

    void logParsedProjects()
    {
        m_dependsWorker.poll();

        int currentIteration = 1;
        qDebug() << "--------------------------------------------------------------------------------------------------------";
        qDebug() << "\033[32mFound apps:\033[0m";
        for (Project & app : apps)
        {
            qDebug() << "\033[33mAPP N:" << currentIteration++ << "\033[0m"   << endl
                     << "NAME:  " << app.name                                 << endl
                     << "SRC:   " << app.srcFilePath                          << endl
                     << "DEPS:  " << app.dependFilePath                       << endl
                     << "DEPON: " << app.depends.join(", ")                   << endl
                        ;
        }

        qDebug() << "--------------------------------------------------------------------------------------------------------";

        currentIteration = 1;
        qDebug() << "\033[32mFound libraries:\033[0m";
        for (Project & lib : libs)
        {
            qDebug() << "\033[33mLIBRARY N:" << currentIteration++ << "\033[0m" << endl
                     << "NAME:" << lib.name                                     << endl
                     << "SRC: " << lib.srcFilePath                              << endl
                     << "DEPS:" << lib.dependFilePath                           << endl
                     << "USE: " << lib.useFilePath
                        ;
        }
        qDebug() << "--------------------------------------------------------------------------------------------------------";
    }

    void setPath(const QString & path)
    {
        m_searcher.setPath(path);
        m_dependsWorker.setPath(path);
    }

    bool backupAll(const QString & backupDirectory)
    {
        m_dependsWorker.poll();

        if (!m_backupManager.cd(backupDirectory))
        {
            qDebug() << "[INTERFACE] Error setting backup directory";
            return false;
        }

        bool result = true;
        for (Project & app : apps)
        {
            if (!m_backupManager.backup(app.name, app.srcFilePath) ||
                !m_backupManager.backup(app.name, app.dependFilePath))
                result = false;
        }

        for (Project & lib : libs)
        {
            if (!m_backupManager.backup(lib.name, lib.srcFilePath) ||
                !m_backupManager.backup(lib.name, lib.useFilePath) ||
                !m_backupManager.backup(lib.name, lib.dependFilePath))
                result = false;
        }
        return result;
    }

    bool loadBackup(const QString & backupDirectory)
    {
        m_dependsWorker.poll();

        if (!m_backupManager.cd(backupDirectory))
        {
            qDebug() << "[INTERFACE] Error setting backup directory";
            return false;
        }

        apps.clear();
        libs.clear();

        bool result = m_backupManager.loadAll();

        m_searcher.findFiles();
        m_dependsWorker.parseFiles();

        return result;
    }
};

ProjectDirectoryFileInterface::ProjectDirectoryFileInterface() :
    m_pImpl {new Impl}
{

}

ProjectDirectoryFileInterface::~ProjectDirectoryFileInterface()
{

}

int ProjectDirectoryFileInterface::processDirectory(const QString path)
{
    m_pImpl->m_dependsWorker.poll();

    m_pImpl->setPath(path);

    m_pImpl->m_searcher.findFiles();
    m_pImpl->m_dependsWorker.parseFiles();
    m_pImpl->logParsedProjects();

    m_pImpl->m_dependsWorker.poll();

    return (m_pImpl->apps.size() + m_pImpl->libs.size());
}

QStringList ProjectDirectoryFileInterface::getLibraryNameList()
{
    m_pImpl->m_dependsWorker.poll();
    QStringList result;
    for (const Project & lib : m_pImpl->libs)
    {
        result << lib.name;
    }
    return result;
}

QStringList ProjectDirectoryFileInterface::getAppNameList()
{
    m_pImpl->m_dependsWorker.poll();
    QStringList result;
    for (const Project & app : m_pImpl->apps)
    {
        result << app.name;
    }
    return result;
}

QString ProjectDirectoryFileInterface::currentDirectory() const { return m_pImpl->m_searcher.basePath(); }

void ProjectDirectoryFileInterface::addLibrary(const QString &appName, const QString &libraryName) { m_pImpl->m_dependsWorker.addLibrary(appName, libraryName); }
void ProjectDirectoryFileInterface::removeLibrary(const QString &appName, const QString &libraryName) { m_pImpl->m_dependsWorker.removeLibrary(appName, libraryName); }
QStringList ProjectDirectoryFileInterface::getDepends(const QString &appName) { return m_pImpl->m_dependsWorker.getDepends(appName); }

void ProjectDirectoryFileInterface::saveChanges()
{
    backupAll("./saveChangesBackup");
    m_pImpl->m_dependsWorker.saveChanges();
}

int ProjectDirectoryFileInterface::progressPercent() const
{
    return m_pImpl->m_dependsWorker.progressPercent();
}

void ProjectDirectoryFileInterface::poll() { m_pImpl->m_dependsWorker.poll(); }

bool ProjectDirectoryFileInterface::backupAll(const QString & backupDirectory) { return m_pImpl->backupAll(backupDirectory); }
bool ProjectDirectoryFileInterface::loadBackup(const QString & backupDirectory) { return m_pImpl->loadBackup(backupDirectory); }
