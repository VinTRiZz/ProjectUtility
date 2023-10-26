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

    void parseDepends(Project & proj);

    void writeDepends(Project & proj);

private:
    QVector<Project> & apps;
    QVector<Project> & libs;

    QString currentBasePath;

};

}

#endif // DEPENDENCYPARSER_H
