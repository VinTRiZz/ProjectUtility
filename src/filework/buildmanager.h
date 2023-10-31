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

    void waitForRebuild();

    bool isWorking() const;

    void setLogFile(const QString & logPath);

signals:
    void buildComplete(const Project & proj, bool buildResult);

private:
    bool m_isWorking {false};

    void writeLog(const QByteArray & what);
    bool invoke(const QString & program, const QStringList args, const int timeout);

    QFile m_logFile;
};

}

#endif // BUILDMANAGER_H
