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
    FileSearcher(QVector<Project> & apps, QVector<Project> & libs, UtilFunctionClass & utilClass);
    ~FileSearcher();

    void setPath(const QString & path);
    QString basePath() const;

    void findFiles();

private:
    QString currentBasePath;
    QString findOutput;
    QVector<Project> & apps;
    QVector<Project> & libs;
    UtilFunctionClass & m_utilClass;

    bool searchForProjects(const QString & basePath, bool isLibs);
};

}

#endif // FILESEARCHER_H
