#include "projectdirectoryfileinterface.h"

#include "filesearcher.h"
#include "backupmanager.h"
#include "dependsworker.h"
#include "buildmanager.h"
#include "archivator.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

#include <thread>

#define BUILD_LOG_FILE_NAME "buildLog.txt"

static const QString SAVE_CHANGES_BACKUP_DIRECTORY {"./saveChangesBackup"};

using namespace FileWork;

struct ProjectDirectoryFileInterface::Impl
{
    std::thread * processThread {nullptr};

    QVector<Project> apps;
    QVector<Project> libs;

    QString currentBasePath;

    FileSearcher m_searcher{ apps, libs };
    DependsWorker m_dependsWorker {apps, libs };

    BuildManager m_buildManager;
    Archivator m_archivator;

    BackupManager m_backupManager;

    Impl(QObject * parent) :
        m_buildManager{parent}
    {
        m_buildManager.setLogFile( QDir::currentPath() + "/" + BUILD_LOG_FILE_NAME );
    }

    Project * getProject(const QString & projectName)
    {
        auto projectPos = std::find_if(apps.begin(), apps.end(), [&projectName](Project & app){ return (app.name == projectName); });

        if (projectPos == apps.end())
        {
            projectPos = std::find_if(libs.begin(), libs.end(), [&projectName](Project & app){ return (app.name == projectName); });

            if (projectPos == libs.end())
                return nullptr;
        }

        return projectPos;
    }

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
                     << "PRO:   " << app.projectProFilePath                   << endl
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
                     << "NAME: " << lib.name                                    << endl
                     << "PRO:  " << lib.projectProFilePath                      << endl
                     << "DEPS: " << lib.dependFilePath                          << endl
                     << "USE:  " << lib.useFilePath
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
            if (!m_backupManager.backup(app.name, app.dependFilePath))
                result = false;
        }

        for (Project & lib : libs)
        {
            if (!m_backupManager.backup(lib.name, lib.useFilePath) ||
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

ProjectDirectoryFileInterface::ProjectDirectoryFileInterface(QObject * parent) :
    QObject(parent),
    m_pImpl {new Impl(parent) }
{
    connect(&m_pImpl->m_archivator, &Archivator::archiveComplete, this, &ProjectDirectoryFileInterface::archiveComplete);
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

bool ProjectDirectoryFileInterface::addLibrary(const QString &projectName, const QString &libraryName)
{
    m_pImpl->m_dependsWorker.addLibrary(m_pImpl->getProject(projectName), libraryName);
}

void ProjectDirectoryFileInterface::removeLibrary(const QString &projectName, const QString &libraryName)
{
    m_pImpl->m_dependsWorker.removeLibrary(m_pImpl->getProject(projectName), libraryName);
}

QStringList ProjectDirectoryFileInterface::getDepends(const QString &appName)
{
    auto pProj = m_pImpl->getProject(appName);

    if (pProj)
        return pProj->depends;
    return QStringList();
}

void ProjectDirectoryFileInterface::saveChanges()
{
    // backupAll(SAVE_CHANGES_BACKUP_DIRECTORY);
    m_pImpl->m_dependsWorker.saveChanges();
}

int ProjectDirectoryFileInterface::progressPercent() const
{
    return m_pImpl->m_dependsWorker.progressPercent();
}

void ProjectDirectoryFileInterface::poll() { m_pImpl->m_dependsWorker.poll(); }

bool ProjectDirectoryFileInterface::backupAll(const QString & backupDirectory) { return m_pImpl->backupAll(backupDirectory); }
bool ProjectDirectoryFileInterface::loadBackup(const QString & backupDirectory) { return m_pImpl->loadBackup(backupDirectory); }

bool ProjectDirectoryFileInterface::build(const QString &projectName, const QString &target)
{
    return m_pImpl->m_buildManager.build(*m_pImpl->getProject(projectName), target);
}

bool ProjectDirectoryFileInterface::rebuild(const QString &projectName, const QString &target)
{
    return m_pImpl->m_buildManager.rebuild(*m_pImpl->getProject(projectName), target);
}

void ProjectDirectoryFileInterface::archiveProject(const QString &projectName, const QString &resultPath)
{
    const QString projectPath = QFileInfo(m_pImpl->getProject(projectName)->projectProFilePath).absolutePath();

    m_pImpl->m_archivator.archive(projectPath, resultPath);
}

void ProjectDirectoryFileInterface::archiveSelectedProjects(const QStringList &projectNames, const QString &resultPath)
{
    m_pImpl->m_archivator.clear();
    for (auto & projectName : projectNames)
    {
        m_pImpl->m_archivator.addProject(QFileInfo(m_pImpl->getProject(projectName)->projectProFilePath).absolutePath());
    }
    m_pImpl->m_archivator.archive(resultPath);
}

void ProjectDirectoryFileInterface::archiveAllProjects(const QString & resultPath)
{
    m_pImpl->m_archivator.clear();

    for (auto & app : m_pImpl->apps)
    {
        m_pImpl->m_archivator.addProject(QFileInfo(app.projectProFilePath).absolutePath());
    }

    for (auto & lib : m_pImpl->libs)
    {
        m_pImpl->m_archivator.addProject(QFileInfo(lib.projectProFilePath).absolutePath());
    }

    m_pImpl->m_archivator.archive(resultPath);
}

bool ProjectDirectoryFileInterface::archiveSucceed() const
{
    return m_pImpl->m_archivator.archived();
}
