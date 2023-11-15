#ifndef PROJECTDIRECTORYFILEINTERFACE_H
#define PROJECTDIRECTORYFILEINTERFACE_H

#include <memory>
#include <QString>
#include <QObject>

#include "gui/dependencygraphwidget.h"
#include "projectbasegenerator.h"

namespace DependsSearcher
{

class ProjectDirectoryFileInterface : public QObject
{
    Q_OBJECT
public:
    ProjectDirectoryFileInterface(QObject * parent);
    ~ProjectDirectoryFileInterface();

    void setGraphWidget(GraphWidget::DependencyGraphWidget * pGraphWidget);

    // Returns count of files found
    int processDirectory(const QString path);
    QString currentDirectory() const;

    void setCurrentHead(const QString & projectName);

    QStringList getLibraryNameList();
    QStringList getAppNameList();

    bool addLibrary(const QString & projectName, const QString & libraryName);
    void removeLibrary(const QString & projectName, const QString & libraryName);

    void saveChanges();

    QStringList getDepends(const QString & appName);

    void poll();

    bool backupAll(const QString & backupDirectory);
    bool loadBackup(const QString & backupDirectory);

    bool addBuild(const QString & projectName, const QString & target);
    bool addRebuild(const QString & projectName, const QString & target);
    bool startBuild();

    void archiveProject(const QString & projectName, const QString & resultPath);
    void archiveSelectedProjects(const QStringList & projectNames, const QString & resultPath);
    void archiveAllProjects(const QString & resultPath);

    bool hasDependRecurse(const QString &projName, const QString &depName);

    Configuration::ProjectConfiguration & mainConfig();
    void saveCurrentConfiguration();
    void loadConfiguration();

    void reloadGraph();

    bool generateProject(const ProjectBaseConfiguration & config);

signals:
    void archiveComplete(bool result);
    void buildComplete(const QString & projectName, bool buildResult);

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // PROJECTDIRECTORYFILEINTERFACE_H
