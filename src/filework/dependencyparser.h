#ifndef DEPENDENCYPARSER_H
#define DEPENDENCYPARSER_H

#include "filesearcher.h"

namespace FileWork
{

class DependencyParser
{
public:
    DependencyParser(QVector<Project> & apps, QVector<Project> & libs);
    ~DependencyParser();

    void setPath(const QString & path);

    void parseAllDepends();

private:
    QVector<Project> & apps;
    QVector<Project> & libs;

    QString currentBasePath;

    void parseDepends(Project & proj);
};

}

#endif // DEPENDENCYPARSER_H
