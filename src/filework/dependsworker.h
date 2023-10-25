#ifndef DEPENDSWORKER_H
#define DEPENDSWORKER_H

#include "filesearcher.h"
#include "dependencyparser.h"

#include <QString>
#include <thread>

namespace FileWork
{

class DependsWorker
{
public:
    DependsWorker(QVector<Project> & apps, QVector<Project> & libs);
    ~DependsWorker();

    void addLibrary(const QString &appName, const QString &libraryName);
    void removeLibrary(const QString &appName, const QString &libraryName);

    QStringList getDepends(const QString &appName);

    void updateDepends();
    void poll();

    void setPath(const QString & path);

    void parseFiles();
    void setupDependsFromFiles(Project & proj);

private:
    QVector<Project> & apps;
    QVector<Project> & libs;

    std::thread * processThread {nullptr};

    DependencyParser m_depParser;

    QString currentDirectory;
};

}

#endif // DEPENDSWORKER_H
