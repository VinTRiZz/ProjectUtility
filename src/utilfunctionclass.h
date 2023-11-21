#ifndef UTILFUNCTIONCLASS_H
#define UTILFUNCTIONCLASS_H

#include <QVector>
#include <QString>
#include <QFile>

#include <atomic>

#include "projectsettings.h"

namespace DependsSearcher
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

class UtilFunctionClass : public QObject
{
    Q_OBJECT
public:
    void logParsedProjects();

    bool invoke(const QString & program, const QStringList & args, const int timeout);
    bool invoke(const QString & program, const QStringList & args, QString & outputBuffer, const int timeout);

    void setLogFile(const QString &logPath);

    void writeLog(const QByteArray & what);
    void writeLog(const QString & what);

    bool hasRecurseDepend(QStringList & dependQuery, Project * pParent);

    Project * getProject(const QString & projectName);
    bool hasDepend(const Project * proj, const QString & libName);

    QStringList getLibraryNameList();
    QStringList getAppNameList();

    void increasePercent(const float value);
    void setPercent(const float newVal);
    float currentPercent() const;

    Configuration::ProjectConfiguration & projectConfiguration();

    static UtilFunctionClass & getInstance(QVector<Project> * initApps = nullptr, QVector<Project> * initLibs = nullptr, Configuration::ProjectConfiguration * mainProjectConfiguration = nullptr);
    ~UtilFunctionClass();

signals:
    void log(const QString & what);

private:
    QVector<Project> * apps;
    QVector<Project> * libs;

    Configuration::ProjectConfiguration * mainProjectConfiguration {nullptr};

    std::atomic<float> processPercent {0};

    QFile m_logFile;

    UtilFunctionClass(QObject * parent = nullptr);
    UtilFunctionClass(QVector<Project> * initApps, QVector<Project> * initLibs, Configuration::ProjectConfiguration * mainProjectConfiguration, QObject * parent = nullptr);
};

}

#endif // UTILFUNCTIONCLASS_H
