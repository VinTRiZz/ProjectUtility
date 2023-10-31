#include "buildmanager.h"

#include <QDebug>
#include <QDir>

#define BUILD_START_TIMEOUT 1000

using namespace FileWork;

BuildManager::BuildManager(QObject * parent) :
    QObject(parent),
    m_utilClass (m_utilClass.getInstance())
{

}

BuildManager::~BuildManager()
{

}

bool BuildManager::build(const Project &proj, const QString target, const int timeout)
{
    if (m_isWorking)
        return false;
    m_isWorking = true;

    m_utilClass.writeLog(QString("Project build \"%1\" with target \"%2\" started").arg(proj.name, target).toUtf8());

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList qmakeArgs;
    qmakeArgs << proj.name + ".pro" << "\-spec" << "linux\-g\+\+";

    if (target == "debug")
        qmakeArgs << "CONFIG+=debug CONFIG+=qml_debug";
    else if (target == "release")
        qmakeArgs << "CONFIG+=qtquickcompiler";
    else
    {
        qDebug() << "[BUILD MANAGER] No target selected";
        m_utilClass.writeLog("No target selected");
        return false;
    }

    QStringList buildArgs;

    // Stage 1
    if (!m_utilClass.invoke("/usr/bin/qmake", qmakeArgs, timeout))
    {
        m_isWorking = false;
        return false;
    }

    // Stage 2
    if (!m_utilClass.invoke("/usr/bin/make", buildArgs, timeout))
    {
        m_isWorking = false;
        return false;
    }

    QDir::setCurrent(currentDir);

    m_isWorking = false;
    return true;
}

bool BuildManager::rebuild(const Project &proj, const QString target, const int timeout)
{
    if (m_isWorking)
        return false;

    m_isWorking = true;

    m_utilClass.writeLog("Project rebuild started");

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList cleanArgs;
    cleanArgs << "clean";

    QDir::setCurrent(projectDir);
    m_utilClass.invoke("/usr/bin/make", cleanArgs, timeout);
    QDir::setCurrent(currentDir);

    m_isWorking = false;
    return build(proj, target, timeout);
}
