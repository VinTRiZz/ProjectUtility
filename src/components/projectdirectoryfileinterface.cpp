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

using namespace DependsSearcher;

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

    BackupManager m_backupManager {mainProjectConfiguration};

    ProjectBaseGenerator m_projectGenerator {m_utilClass};

    GraphWidget::DependencyGraphWidget * m_pGraphWidget;

    Impl(QObject * parent) :
        m_buildManager{parent}
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

        // Check for recurses
        QStringList depQuery;
        for (DependsSearcher::Project & proj : apps)
        {
            depQuery.clear();
            if (m_utilClass.hasRecurseDepend(depQuery, &proj))
            {
                qDebug() << "[FILE INTERFACE] Found infinity depend, vector not inited";
                return depsVect;
            }
        }

        // Convert all apps
        for (DependsSearcher::Project & proj : apps)
        {
            pBufferStruct = new GraphWidget::DependencyStruct();

            pBufferStruct->isApp = !proj.isLibrary;
            pBufferStruct->name = proj.name;

            depsVect.push_back(pBufferStruct);
        }

        // Convert all libs
        for (DependsSearcher::Project & proj : libs)
        {
            pBufferStruct = new GraphWidget::DependencyStruct();

            pBufferStruct->isApp = !proj.isLibrary;
            pBufferStruct->name = proj.name;

            depsVect.push_back(pBufferStruct);
        }

        // Convert depends
        GraphWidget::DependencyStruct * pDependStruct;

        // Work for apps
        for (DependsSearcher::Project & proj : apps)
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
        for (DependsSearcher::Project & proj : libs)
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

ProjectDirectoryFileInterface::ProjectDirectoryFileInterface(QObject * parent) :
    QObject(parent),
    m_pImpl {new Impl(parent) }
{
    connect(&m_pImpl->m_archivator, &Archivator::archiveComplete, this, &ProjectDirectoryFileInterface::archiveComplete);
    connect(&m_pImpl->m_buildManager, &BuildManager::buildComplete, this, &ProjectDirectoryFileInterface::buildComplete);
}

ProjectDirectoryFileInterface::~ProjectDirectoryFileInterface()
{

}

void ProjectDirectoryFileInterface::setGraphWidget(GraphWidget::DependencyGraphWidget *pGraphWidget)
{
    m_pImpl->m_pGraphWidget = pGraphWidget;
}

int ProjectDirectoryFileInterface::processDirectory(const QString path)
{
    m_pImpl->m_dependsWorker.poll();

    m_pImpl->setPath(path);

    m_pImpl->m_searcher.findFiles();
    m_pImpl->m_dependsWorker.parseFiles();
    m_pImpl->m_dependsWorker.poll();
    m_pImpl->m_dependsWorker.replaceUnknown();
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

void ProjectDirectoryFileInterface::setCurrentHead(const QString &projectName)
{
    Project * pProject = m_pImpl->m_utilClass.getProject(projectName);

    if (pProject)
        m_pImpl->m_pGraphWidget->setHead(projectName);
}

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
        m_pImpl->m_pGraphWidget->update();
        return pProj->depends;
    }
    return QStringList();
}

void ProjectDirectoryFileInterface::saveChanges()
{
    // backupAll(Backup directory for changes);
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

bool ProjectDirectoryFileInterface::hasDependRecurse(const QString &projName, const QString &depName)
{
    Project * pProj = m_pImpl->m_utilClass.getProject(projName);

    if (!pProj)
    {
        qDebug() << "[FILE INTERFACE] Error: Project not found:" << projName;
        return false;
    }

    if (!m_pImpl->m_utilClass.getProject(depName))
    {
        qDebug() << "[FILE INTERFACE] Error: Depend project not found:" << depName;
        return false;
    }

    return m_pImpl->m_utilClass.hasDepend(pProj, depName);
}

Configuration::ProjectConfiguration &ProjectDirectoryFileInterface::configuration()
{
    return m_pImpl->mainProjectConfiguration;
}

void ProjectDirectoryFileInterface::saveCurrentConfiguration()
{
    const QString configPath = m_pImpl->mainProjectConfiguration.strSettings["Configuration file path"];

    qDebug() << "[FILE INTERFACE] Saving settings to path:" << configPath;
    QSettings configFile(configPath, QSettings::Format::IniFormat);
    QString writeBuffer;

    configFile.beginGroup("StringSettings");
    for (auto & configPair : m_pImpl->mainProjectConfiguration.strSettings)
    {
        qDebug() << "[FILE INTERFACE] Saving setting:" << configPair.first << "Its value:" << configPair.second;
        writeBuffer = configPair.second.toUtf8().toBase64();
        configFile.setValue(configPair.first, writeBuffer);
    }
    configFile.endGroup();

    configFile.beginGroup("IntSettings");
    for (auto & configPair : m_pImpl->mainProjectConfiguration.intSettings)
    {
        configFile.setValue(configPair.first, QString::number(configPair.second));
    }
    configFile.endGroup();
    qDebug() << "[FILE INTERFACE] Setting loaded";
}

void ProjectDirectoryFileInterface::loadConfiguration()
{
    const QString configPath = m_pImpl->mainProjectConfiguration.strSettings["Configuration file path"];

    qDebug() << "[FILE INTERFACE] Loading settings by path:" << configPath;

    if (!QFileInfo(configPath).exists())
    {
        qDebug() << "[FILE INTERFACE] Configuration file not found";
        return;
    }

    QSettings configFile(configPath, QSettings::Format::IniFormat);
    QString writeBuffer;

    configFile.beginGroup("StringSettings");
    for (auto & configPair : m_pImpl->mainProjectConfiguration.strSettings)
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

        qDebug() << "[FILE INTERFACE] Read setting:" << configPair.first << "Its value:" << configPair.second;
    }
    configFile.endGroup();

    configFile.beginGroup("IntSettings");
    for (auto & configPair : m_pImpl->mainProjectConfiguration.intSettings)
    {
        configPair.second = Configuration::defaultProjectConfiguration.intSettings[configPair.first];
        configPair.second = configFile.value(configPair.first).toInt();
    }
    configFile.endGroup();
    qDebug() << "[FILE INTERFACE] Setting loaded";
}

void ProjectDirectoryFileInterface::reloadGraph()
{
    m_pImpl->m_pGraphWidget->clear();
    m_pImpl->m_pGraphWidget->setDependsVector( m_pImpl->createDependsVector() );
    m_pImpl->m_pGraphWidget->update();
}

bool ProjectDirectoryFileInterface::generateProject(const ProjectBaseConfiguration &config)
{
    return m_pImpl->m_projectGenerator.generateProject(config);
}
