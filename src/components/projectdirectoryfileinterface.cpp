#include "projectdirectoryfileinterface.h"

#include "filesearcher.h"
#include "backupmanager.h"
#include "dependsworker.h"
#include "buildmanager.h"
#include "archivator.h"

#include "projectsettings.h"

#include <QSettings>

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

#include <thread>

using namespace ProjectUtility;

struct ProjectDirectoryFileInterface::Impl
{
    Configuration::ProjectConfiguration mainProjectConfiguration { Configuration::ProjectConfiguration() };

    std::thread * processThread {nullptr};

    QVector<Project> apps;
    QVector<Project> libs;
    QVector<Project> unknownLibraries;

    QString currentBasePath;

    UtilFunctionClass & m_utilClass{ UtilFunctionClass::getInstance(&apps, &libs, &mainProjectConfiguration)};

    FileSearcher m_searcher{ apps, libs, m_utilClass};
    DependsWorker m_dependsWorker {apps, libs};

    BuildManager m_buildManager;
    Archivator m_archivator {m_utilClass};

    BackupManager m_backupManager {m_utilClass};

    ProjectBaseGenerator m_projectGenerator {m_utilClass};

    GraphWidget::DependencyGraphWidget * m_pGraphWidget;

    Impl(QObject * parent) :
        m_buildManager{parent, m_utilClass}
    {
        m_utilClass.setLogFile( QDir::currentPath() + "/" + mainProjectConfiguration.strSettings["Log file name"] );
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
            m_utilClass.logChannel() << "[INTERFACE] Error setting backup directory";
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
            m_utilClass.logChannel() << "[INTERFACE] Error setting backup directory";
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
        m_utilClass.logChannel() << "[FILE INTERFACE] Creating depend recursive vector";
        QVector<GraphWidget::DependencyStruct *> depsVect;
        GraphWidget::DependencyStruct * pBufferStruct;

        // Check for recurses
        QStringList depQuery;
        for (ProjectUtility::Project & proj : apps)
        {
            depQuery.clear();
            if (m_utilClass.hasRecurseDepend(depQuery, &proj))
            {
                m_utilClass.logChannel() << "[FILE INTERFACE] Found infinity depend, vector not inited";
                return depsVect;
            }
        }

        // Convert all apps
        for (ProjectUtility::Project & proj : apps)
        {
            pBufferStruct = new GraphWidget::DependencyStruct();

            pBufferStruct->isApp = !proj.isLibrary;
            pBufferStruct->name = proj.name;

            depsVect.push_back(pBufferStruct);
        }

        // Convert all libs
        for (ProjectUtility::Project & proj : libs)
        {
            pBufferStruct = new GraphWidget::DependencyStruct();

            pBufferStruct->isApp = !proj.isLibrary;
            pBufferStruct->name = proj.name;

            depsVect.push_back(pBufferStruct);
        }

        // Convert depends
        GraphWidget::DependencyStruct * pDependStruct;

        // Work for apps
        for (ProjectUtility::Project & proj : apps)
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
        for (ProjectUtility::Project & proj : libs)
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

        m_utilClass.logChannel() << "[FILE INTERFACE] Depend recursive vector \033[32mcreated\033[0m";
        return depsVect;
    }
};

ProjectDirectoryFileInterface::ProjectDirectoryFileInterface(QObject * parent) :
    QObject(parent),
    d {new Impl(parent) }
{
    connect(&d->m_archivator, &Archivator::archiveComplete, this, &ProjectDirectoryFileInterface::archiveComplete);
    connect(&d->m_buildManager, &BuildManager::buildComplete, this, &ProjectDirectoryFileInterface::buildComplete);
    connect(&d->m_utilClass, &UtilFunctionClass::log, this, &ProjectDirectoryFileInterface::log);
}

ProjectDirectoryFileInterface::~ProjectDirectoryFileInterface()
{

}

UtilFunctionClass &ProjectDirectoryFileInterface::utilClass()
{
    return d->m_utilClass;
}

void ProjectDirectoryFileInterface::setGraphWidget(GraphWidget::DependencyGraphWidget *pGraphWidget)
{
    d->m_pGraphWidget = pGraphWidget;
}

int ProjectDirectoryFileInterface::processDirectory(const QString path)
{
    d->m_dependsWorker.poll();

    d->setPath(path);

    d->m_searcher.findFiles();
    d->m_dependsWorker.parseFiles();
    d->m_dependsWorker.poll();
    d->m_dependsWorker.replaceUnknown();
    d->m_utilClass.logParsedProjects();

    d->m_dependsWorker.poll();

    d->m_pGraphWidget->clear();
    d->m_pGraphWidget->setDependsVector( d->createDependsVector() );

    return (d->apps.size() + d->libs.size());
}

QStringList ProjectDirectoryFileInterface::getLibraryNameList()
{
    d->m_dependsWorker.poll();
    return d->m_utilClass.getLibraryNameList();
}

QStringList ProjectDirectoryFileInterface::getAppNameList()
{
    d->m_dependsWorker.poll();
    return d->m_utilClass.getAppNameList();
}

QString ProjectDirectoryFileInterface::currentDirectory() const { return d->m_searcher.basePath(); }

void ProjectDirectoryFileInterface::setCurrentHead(const QString &projectName)
{
    Project * pProject = d->m_utilClass.getProject(projectName);

    if (pProject)
        d->m_pGraphWidget->setHead(projectName);
}

bool ProjectDirectoryFileInterface::addLibrary(const QString &projectName, const QString &libraryName)
{
    return d->m_dependsWorker.addLibrary(d->m_utilClass.getProject(projectName), libraryName);
}

void ProjectDirectoryFileInterface::removeLibrary(const QString &projectName, const QString &libraryName)
{
    d->m_dependsWorker.removeLibrary(d->m_utilClass.getProject(projectName), libraryName);
}

QStringList ProjectDirectoryFileInterface::getDepends(const QString &appName)
{
    auto pProj = d->m_utilClass.getProject(appName);

    if (pProj)
    {
        d->m_pGraphWidget->setHead(appName);
        d->m_pGraphWidget->update();
        return pProj->depends;
    }
    return QStringList();
}

void ProjectDirectoryFileInterface::saveChanges()
{
    // backupAll(Backup directory for changes);
    d->m_dependsWorker.saveChanges();
}

void ProjectDirectoryFileInterface::poll() { d->m_dependsWorker.poll(); }

bool ProjectDirectoryFileInterface::backupAll(const QString & backupDirectory) { return d->backupAll(backupDirectory); }
bool ProjectDirectoryFileInterface::loadBackup(const QString & backupDirectory) { return d->loadBackup(backupDirectory); }

bool ProjectDirectoryFileInterface::addBuild(const QString &projectName, const QString &target)
{
    BuildProjectHandle buildHandle;

    buildHandle.project = *d->m_utilClass.getProject(projectName);
    buildHandle.target = target;

    return d->m_buildManager.build(buildHandle);
}

bool ProjectDirectoryFileInterface::addRebuild(const QString &projectName, const QString &target)
{
    BuildProjectHandle buildHandle;

    buildHandle.project = *d->m_utilClass.getProject(projectName);
    buildHandle.target = target;

    return d->m_buildManager.rebuild(buildHandle);
}

bool ProjectDirectoryFileInterface::startBuild()
{
    return d->m_buildManager.startBuilding();
}

void ProjectDirectoryFileInterface::archiveProject(const QString &projectName, const QString &resultPath)
{
    const QString projectPath = QFileInfo(d->m_utilClass.getProject(projectName)->projectProFilePath).absolutePath();

    d->m_archivator.archive(projectPath, resultPath);
}

void ProjectDirectoryFileInterface::archiveSelectedProjects(const QStringList &projectNames, const QString &resultPath)
{
    d->m_archivator.clear();
    for (auto & projectName : projectNames)
    {
        d->m_archivator.addProject(QFileInfo(d->m_utilClass.getProject(projectName)->projectProFilePath).absolutePath());
    }
    d->m_archivator.archive(resultPath);
}

void ProjectDirectoryFileInterface::archiveAllProjects(const QString & resultPath)
{
    d->m_archivator.clear();

    for (auto & app : d->apps)
    {
        d->m_archivator.addProject(QFileInfo(app.projectProFilePath).absolutePath());
    }

    for (auto & lib : d->libs)
    {
        d->m_archivator.addProject(QFileInfo(lib.projectProFilePath).absolutePath());
    }

    d->m_archivator.archive(resultPath);
}

bool ProjectDirectoryFileInterface::hasDependRecurse(const QString &projName, const QString &depName)
{
    Project * pProj = d->m_utilClass.getProject(projName);

    if (!pProj)
    {
        d->m_utilClass.logChannel() << "[FILE INTERFACE] Error: Project not found:" << projName;
        return false;
    }

    if (!d->m_utilClass.getProject(depName))
    {
        d->m_utilClass.logChannel() << "[FILE INTERFACE] Error: Depend project not found:" << depName;
        return false;
    }

    return d->m_utilClass.hasDepend(pProj, depName);
}

Configuration::ProjectConfiguration &ProjectDirectoryFileInterface::configuration()
{
    return d->mainProjectConfiguration;
}

void ProjectDirectoryFileInterface::saveCurrentConfiguration()
{
    const QString configPath = d->mainProjectConfiguration.strSettings["Configuration file path"];

    if (QFile::remove(configPath))
    {
        d->m_utilClass.logChannel() << "[FILE INTERFACE] Previous config file erased";
    }

    d->m_utilClass.logChannel() << "[FILE INTERFACE] Saving settings to path:" << configPath;
    QSettings configFile(configPath, QSettings::Format::IniFormat);
    QString writeBuffer;

    configFile.beginGroup("StringSettings");
    for (auto & configPair : d->mainProjectConfiguration.strSettings)
    {
        d->m_utilClass.logChannel() << "[FILE INTERFACE] Saving setting:" << configPair.first << "Its value:" << (QString)configPair.second;
        writeBuffer = configPair.second.toUtf8().toBase64();
        configFile.setValue(configPair.first, writeBuffer);
    }
    configFile.endGroup();

    configFile.beginGroup("IntSettings");
    for (auto & configPair : d->mainProjectConfiguration.intSettings)
    {
        configFile.setValue(configPair.first, QString::number(configPair.second));
    }
    configFile.endGroup();
    d->m_utilClass.logChannel() << "[FILE INTERFACE] Setting loaded";
}

void ProjectDirectoryFileInterface::loadConfiguration()
{
    const QString configPath = d->mainProjectConfiguration.strSettings["Configuration file path"];

    d->m_utilClass.logChannel() << "[FILE INTERFACE] Loading settings by path:" << configPath;

    if (!QFileInfo(configPath).exists())
    {
        d->m_utilClass.logChannel() << "[FILE INTERFACE] Configuration file not found";
        return;
    }

    QSettings configFile(configPath, QSettings::Format::IniFormat);
    QString writeBuffer;

    configFile.beginGroup("StringSettings");
    for (auto & configPair : d->mainProjectConfiguration.strSettings)
    {
        configPair.second = "";

        if (!configFile.contains(configPair.first))
        {
            configPair.second = Configuration::defaultProjectConfiguration.strSettings[configPair.first]; // If configuration not found, setup as default
            continue;
        }

        writeBuffer = configFile.value(configPair.first).toString();

        writeBuffer = QByteArray::fromBase64(writeBuffer.toUtf8());

        configPair.second = writeBuffer;

        d->m_utilClass.logChannel() << "[FILE INTERFACE] Read setting:" << configPair.first << "Its value:" << (QString)configPair.second;
    }
    configFile.endGroup();

    configFile.beginGroup("IntSettings");
    for (auto & configPair : d->mainProjectConfiguration.intSettings)
    {
        configPair.second = Configuration::defaultProjectConfiguration.intSettings[configPair.first];
        configPair.second = configFile.value(configPair.first).toInt();
    }
    configFile.endGroup();
    d->m_utilClass.logChannel() << "[FILE INTERFACE] Setting loaded";
}

void ProjectDirectoryFileInterface::reloadGraph()
{
    d->m_pGraphWidget->clear();
    d->m_pGraphWidget->setDependsVector( d->createDependsVector() );
    d->m_pGraphWidget->update();
}

bool ProjectDirectoryFileInterface::generateProject(const ProjectBaseConfiguration &config)
{
    return d->m_projectGenerator.generateProject(config);
}
