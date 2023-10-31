#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "utilfunctionclass.h"

#include <QObject>
#include <QFile>

// 1 hour timeout :)
#define BUILD_TIMEOUT 3600000

namespace FileWork
{

class BuildManager : public QObject
{
    Q_OBJECT
public:
    BuildManager(QObject * parent);
    ~BuildManager();

    bool build(const Project &proj, const QString target, const int timeout = BUILD_TIMEOUT);
    bool rebuild(const Project &proj, const QString target, const int timeout = BUILD_TIMEOUT);

signals:
#warning "Need to write-up signal proceed"
    void buildComplete(const Project & proj, bool buildResult);

private:
    bool m_isWorking {false};

    QFile m_logFile;

    UtilFunctionClass & m_utilClass;
};

}

#endif // BUILDMANAGER_H
