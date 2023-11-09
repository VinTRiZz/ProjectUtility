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

    UtilFunctionClass & m_utilClass;

    FileSearcher m_searcher{ apps, libs };
    DependsWorker m_dependsWorker {apps, libs };

    BuildManager m_buildManager;
    Archivator m_archivator;

    BackupManager m_backupManager;

    GraphWidget::DependencyGraphWidget * m_pGraphWidget;

    Impl(QObject * parent, GraphWidget::DependencyGraphWidget * displayWidget) :
        m_utilClass( UtilFunctionClass::getInstance(&apps, &libs) ),
        m_buildManager{parent},
        m_pGraphWidget(displayWidget)
    {
        m_utilClass.setLogFile( QDir::currentPath() + "/" + BUILD_LOG_FILE_NAME );
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

    QVector<GraphWidget::DependencyStruct *> createDependsVector()
    {
        qDebug() << "[FILE INTERFACE] Creating depend recursive vector";
        QVector<GraphWidget::DependencyStruct *> depsVect;
        GraphWidget::DependencyStruct * pBufferStruct;

        // Convert all apps
        for (FileWork::Project & proj : apps)
        {
            pBufferStruct = new GraphWidget::DependencyStruct();

            pBufferStruct->isApp = !proj.isLibrary;
            pBufferStruct->name = proj.name;

            depsVect.push_back(pBufferStruct);
        }

        // Convert all libs
        for (FileWork::Project & proj : libs)
        {
            pBufferStruct = new GraphWidget::DependencyStruct();

            pBufferStruct->isApp = !proj.isLibrary;
            pBufferStruct->name = proj.name;

            depsVect.push_back(pBufferStruct);
        }

        for (GraphWidget::DependencyStruct * pStruct : depsVect)
        {
            qDebug() << pStruct->name;
        }

        // Convert depends
        GraphWidget::DependencyStruct * pDependStruct;

        // Work for apps
        for (FileWork::Project & proj : apps)
        {
            // Find project by name
            pDependStruct = nullptr;
            for (GraphWidget::DependencyStruct * dep : depsVect)
            {
                if (proj.name == dep->name)
                    pDependStruct = dep;
            }

            // Check if found
            if (!pDependStruct)
                continue;

            // Add depends from strings
            for (QString & depName : proj.depends)
            {
                // Find depend by name
                for (GraphWidget::DependencyStruct * dep : depsVect)
                {
                    // Add depend if exist
                    if (depName == dep->name)
                        pDependStruct->dependsFrom.push_back(dep);
                }
            }
        }

        // Work for libs
        for (FileWork::Project & proj : libs)
        {
            // Find project by name
            pDependStruct = nullptr;
            for (GraphWidget::DependencyStruct * dep : depsVect)
            {
                if (proj.name == dep->name)
                    pDependStruct = dep;
            }

            // Check if found
            if (!pDependStruct)
                continue;

            // Add depends from strings
            for (QString & depName : proj.depends)
            {
                // Find depend by name
                for (GraphWidget::DependencyStruct * dep : depsVect)
                {
                    // Add depend if exist
                    if (depName == dep->name)
                        pDependStruct->dependsFrom.push_back(dep);
                }
            }
        }

        qDebug() << "[FILE INTERFACE] Depend recursive vector \033[32mcreated\033[0m";
        return depsVect;
    }
};

ProjectDirectoryFileInterface::ProjectDirectoryFileInterface(QObject * parent, GraphWidget::DependencyGraphWidget * pGraphWidget) :
    QObject(parent),
    m_pImpl {new Impl(parent, pGraphWidget) }
{
    connect(&m_pImpl->m_archivator, &Archivator::archiveComplete, this, &ProjectDirectoryFileInterface::archiveComplete);
    connect(&m_pImpl->m_buildManager, &BuildManager::buildComplete, this, &ProjectDirectoryFileInterface::buildComplete);
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
    m_pImpl->m_dependsWorker.poll();
    m_pImpl->m_utilClass.logParsedProjects();

    m_pImpl->m_dependsWorker.poll();

    m_pImpl->m_pGraphWidget->clear();
    m_pImpl->m_pGraphWidget->setDependsVector( m_pImpl->createDependsVector() );

    return (m_pImpl->apps.size() + m_pImpl->libs.size());
}

QStringList ProjectDirectoryFileInterface::getLibraryNameList()
{
    m_pImpl->m_dependsWorker.poll();
    return m_pImpl->m_utilClass.getLibraryNameList();
}

QStringList ProjectDirectoryFileInterface::getAppNameList()
{
    m_pImpl->m_dependsWorker.poll();
    return m_pImpl->m_utilClass.getAppNameList();
}

QString ProjectDirectoryFileInterface::currentDirectory() const { return m_pImpl->m_searcher.basePath(); }

bool ProjectDirectoryFileInterface::addLibrary(const QString &projectName, const QString &libraryName)
{
    return m_pImpl->m_dependsWorker.addLibrary(m_pImpl->m_utilClass.getProject(projectName), libraryName);
}

void ProjectDirectoryFileInterface::removeLibrary(const QString &projectName, const QString &libraryName)
{
    m_pImpl->m_dependsWorker.removeLibrary(m_pImpl->m_utilClass.getProject(projectName), libraryName);
}

QStringList ProjectDirectoryFileInterface::getDepends(const QString &appName)
{
    auto pProj = m_pImpl->m_utilClass.getProject(appName);

    if (pProj)
    {
        m_pImpl->m_pGraphWidget->setHead(appName);
        return pProj->depends;
    }
    return QStringList();
}

void ProjectDirectoryFileInterface::saveChanges()
{
    // backupAll(SAVE_CHANGES_BACKUP_DIRECTORY);
    m_pImpl->m_dependsWorker.saveChanges();
}

void ProjectDirectoryFileInterface::poll() { m_pImpl->m_dependsWorker.poll(); }

bool ProjectDirectoryFileInterface::backupAll(const QString & backupDirectory) { return m_pImpl->backupAll(backupDirectory); }
bool ProjectDirectoryFileInterface::loadBackup(const QString & backupDirectory) { return m_pImpl->loadBackup(backupDirectory); }

bool ProjectDirectoryFileInterface::addBuild(const QString &projectName, const QString &target)
{
    BuildProjectHandle buildHandle;

    buildHandle.project = *m_pImpl->m_utilClass.getProject(projectName);
    buildHandle.target = target;

    return m_pImpl->m_buildManager.build(buildHandle);
}

bool ProjectDirectoryFileInterface::addRebuild(const QString &projectName, const QString &target)
{
    BuildProjectHandle buildHandle;

    buildHandle.project = *m_pImpl->m_utilClass.getProject(projectName);
    buildHandle.target = target;

    return m_pImpl->m_buildManager.rebuild(buildHandle);
}

bool ProjectDirectoryFileInterface::startBuild()
{
    return m_pImpl->m_buildManager.startBuilding();
}

void ProjectDirectoryFileInterface::archiveProject(const QString &projectName, const QString &resultPath)
{
    const QString projectPath = QFileInfo(m_pImpl->m_utilClass.getProject(projectName)->projectProFilePath).absolutePath();

    m_pImpl->m_archivator.archive(projectPath, resultPath);
}

void ProjectDirectoryFileInterface::archiveSelectedProjects(const QStringList &projectNames, const QString &resultPath)
{
    m_pImpl->m_archivator.clear();
    for (auto & projectName : projectNames)
    {
        m_pImpl->m_archivator.addProject(QFileInfo(m_pImpl->m_utilClass.getProject(projectName)->projectProFilePath).absolutePath());
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
