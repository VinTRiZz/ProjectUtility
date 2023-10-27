#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "filesearcher.h"

// 1 hour timeout :)
#define BUILD_TIMEOUT 3600000

namespace FileWork
{

class BuildManager
{
public:
    BuildManager(QVector<Project> & apps, QVector<Project> & libs);
    ~BuildManager();

    bool setArguments(const QStringList args);

    bool build(const QString & projectName, const QString & buildLogFilePath, const int timeout = BUILD_TIMEOUT);
    bool rebuild(const QString & projectName, const QString & buildLogFilePath, const int timeout = BUILD_TIMEOUT);

    bool isWorking() const;

private:
    bool m_isWorking {false};

    QStringList m_buildArgs;

    QVector<Project> & apps;
    QVector<Project> & libs;
};

}

#endif // BUILDMANAGER_H
