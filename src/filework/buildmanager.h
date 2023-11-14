#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "utilfunctionclass.h"

#include "projectsettings.h"

#include <QObject>
#include <QFile>

namespace FileWork
{

struct BuildProjectHandle
{
    Project project;
    QString target;
    int timeout {Configuration::defaultProjectConfiguration.intSettings["Build timeout"]};
};

class BuildManager : public QObject
{
    Q_OBJECT
public:
    BuildManager(QObject * parent);
    ~BuildManager();

    bool build(const BuildProjectHandle & proj);
    bool rebuild(const BuildProjectHandle & proj);

    bool startBuilding();

    void poll();

signals:
    void buildComplete(const QString & projectName, const bool buildResult);

private:
    QThread * m_pProcessThread {nullptr};
    bool m_startingTask {false};

    QVector<BuildProjectHandle> buildQueue;

    UtilFunctionClass & m_utilClass;
};

}

#endif // BUILDMANAGER_H
