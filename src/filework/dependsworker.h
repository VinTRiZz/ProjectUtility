#ifndef DEPENDSWORKER_H
#define DEPENDSWORKER_H

#include "utilfunctionclass.h"
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

    bool addLibrary(Project * proj, const QString &libraryName);
    void removeLibrary(Project * proj, const QString &libraryName);

    void updateDepends();
    void poll();

    void setPath(const QString & path);

    void parseFiles();
    void setupDependsFromFiles(Project & proj);

    void saveChanges();
    int progressPercent() const;

private:
    QVector<Project> & apps;
    QVector<Project> & libs;

    std::thread * processThread {nullptr};

    DependencyParser m_depParser;

    QString currentDirectory;

    UtilFunctionClass & m_utilClass;
};

}

#endif // DEPENDSWORKER_H
