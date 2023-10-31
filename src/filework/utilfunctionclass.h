#ifndef UTILFUNCTIONCLASS_H
#define UTILFUNCTIONCLASS_H

#include <QVector>
#include <QString>

namespace FileWork
{

struct Project
{
    bool isLibrary {false};
    QString name;
    QString projectProFilePath;
    QString dependFilePath;
    QString useFilePath;
    QStringList depends;
};

class UtilFunctionClass
{
public:
    UtilFunctionClass(QVector<Project> & initApps, QVector<Project> & initLibs);
    ~UtilFunctionClass();

private:
    QVector<Project> & apps;
    QVector<Project> & libs;
};

}

#endif // UTILFUNCTIONCLASS_H
