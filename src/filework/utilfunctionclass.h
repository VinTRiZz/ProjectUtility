#ifndef UTILFUNCTIONCLASS_H
#define UTILFUNCTIONCLASS_H

#include <QVector>
#include <QString>
#include <QFile>

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
    bool invoke(const QString & program, const QStringList args, const int timeout);

    void setLogFile(const QString &logPath);
    void writeLog(const QByteArray & what);

    bool hasRecurseDepend(QStringList & dependQuery, Project * pParent);

    static UtilFunctionClass & getInstance(QVector<Project> * initApps = nullptr, QVector<Project> * initLibs = nullptr);

    ~UtilFunctionClass();
private:
    QVector<Project> * apps;
    QVector<Project> * libs;

    QFile m_logFile;

    UtilFunctionClass();
    UtilFunctionClass(QVector<Project> * initApps, QVector<Project> * initLibs);
};

}

#endif // UTILFUNCTIONCLASS_H
