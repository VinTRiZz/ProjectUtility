#include "buildmanager.h"

#include <QDebug>
#include <QProcess>

#define BUILD_START_TIMEOUT 1000

using namespace FileWork;

BuildManager::BuildManager(QVector<Project> & apps, QVector<Project> & libs):
    apps{apps}, libs{libs}
{

}

BuildManager::~BuildManager()
{

}

bool BuildManager::setArguments(const QStringList args)
{
    if (!m_isWorking)
        m_buildArgs = args;
    return !m_isWorking;
}

bool BuildManager::build(const QString &projectName, const QString &buildLogFilePath, const int timeout)
{
    if (m_isWorking)
        return false;

    QStringList buildArgs;

    buildArgs << "";

    buildArgs.append(m_buildArgs);

    if (buildLogFilePath.size() > 1)
        buildArgs << "&>" << buildLogFilePath;

    QProcess buildProcess;

    buildProcess.setProgram("qmake");
    buildProcess.setArguments(buildArgs);

    buildProcess.start();
    if (!buildProcess.waitForStarted(BUILD_START_TIMEOUT))
    {
        qDebug() << "[BUILD MANAGER] \033[31mBuild\033[0m Start timeout, args:"  << buildArgs.join(" ");
        return false;
    }

    if (!buildProcess.waitForFinished(timeout))
    {
        qDebug() << "[BUILD MANAGER] \033[31mBuild\033[0m Finish timeout, args:" << buildArgs.join(" ");
        return false;
    }

    return true;
}

bool BuildManager::rebuild(const QString &projectName, const QString &buildLogFilePath, const int timeout)
{
    if (m_isWorking)
        return false;

    // TODO: Clean

    return build(projectName, buildLogFilePath, timeout);
}
