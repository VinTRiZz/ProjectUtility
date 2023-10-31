#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <QString>
#include <QVector>

#include "utilfunctionclass.h"

namespace FileWork
{

class FileSearcher
{
public:
    FileSearcher(QVector<Project> & apps, QVector<Project> & libs);
    ~FileSearcher();

    void setPath(const QString & path);
    QString basePath() const;

    void findFiles();

private:
    QString currentBasePath;
    QString findOutput;
    QVector<Project> & apps;
    QVector<Project> & libs;

    bool searchForProjects(const QString & basePath, bool isLibs);
//    bool searchForFiles(const QString & basePath);
};

}

#endif // FILESEARCHER_H
