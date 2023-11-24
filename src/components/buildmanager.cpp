#include "buildmanager.h"

#include <QDebug>
#include <QDir>
#include <QThread>

using namespace ProjectUtility;

BuildManager::BuildManager(QObject * parent, UtilFunctionClass &utilClass) :
    QObject(parent),
    m_utilClass (utilClass)
{

}

BuildManager::~BuildManager()
{
    poll();
}

bool BuildManager::build(const BuildProjectHandle & proj)
{
    m_utilClass.logChannel() << "[BUILD MANAGER] Adding task:" << proj.project.name << "with target" << proj.target;
    while (m_startingTask);

    m_startingTask = true;
    buildQueue.push_back(proj);
    m_startingTask = false;

    m_utilClass.logChannel() << "[BUILD MANAGER] Task add complete";
    return true;
}

bool BuildManager::rebuild(const BuildProjectHandle & proj)
{
    m_utilClass.logChannel() << "[BUILD MANAGER] Cleaning build";

    m_utilClass.writeLog(QString("Project rebuild started"));

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.project.projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList cleanArgs;
    cleanArgs << "clean";

    QDir::setCurrent(projectDir);
    bool result = m_utilClass.invoke(m_utilClass.projectConfiguration().strSettings["Make bin path"], cleanArgs, proj.timeout);
    QDir::setCurrent(currentDir);

    if (!result)
        m_utilClass.logChannel() << "[BUILD MANAGER] (Skipped) Error cleaning";

    m_utilClass.logChannel() << "[BUILD MANAGER] Build cleaned";
    return build(proj);
}

bool BuildManager::startBuilding()
{
    poll();
    m_utilClass.logChannel() << "[BUILD MANAGER] Build thread creating";

    m_pProcessThread = QThread::create(
        [this]()
        {
            m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Created";

            BuildProjectHandle proj;

            m_startingTask = true;
            while (buildQueue.size())
            {
                m_startingTask = false;

                m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Asking for project";

                while (m_startingTask);

                m_startingTask = true;
                proj = buildQueue.first();
                buildQueue.pop_front();
                m_startingTask = false;

                m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Building project:" << proj.project.name << "with target" << proj.target;

                m_utilClass.writeLog(QString("Project build \"%1\" with target \"%2\" started").arg(proj.project.name, proj.target).toUtf8());

                const QString currentDir = QDir::currentPath();
                const QString projectDir = QFileInfo(proj.project.projectProFilePath).absolutePath();

                QDir::setCurrent(projectDir);

                QStringList qmakeArgs;
                qmakeArgs << proj.project.name + ".pro" << m_utilClass.projectConfiguration().strSettings["QMake Default args"].toList();

                if (proj.target == "debug")
                    qmakeArgs << m_utilClass.projectConfiguration().strSettings["QMake Debug args"];
                else if (proj.target == "release")
                    qmakeArgs << m_utilClass.projectConfiguration().strSettings["QMake Release args"];
                else
                {
                    m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] No target selected, skipped";
                    emit buildComplete(proj.project.name, false);
                    m_utilClass.writeLog(QString("Build project %1 with target %2: [ERROR: NO TARGET SPECIFIED]").arg(proj.project.name, proj.target));
                    break;
                }

                QStringList buildArgs;

                if (!m_utilClass.projectConfiguration().strSettings["QMake args"].isEmpty())
                {
                    qmakeArgs << m_utilClass.projectConfiguration().strSettings["QMake args"].toList();
                }

                if (!m_utilClass.projectConfiguration().strSettings["Make args"].isEmpty())
                {
                    buildArgs << m_utilClass.projectConfiguration().strSettings["Make args"].toList();
                }

                m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Running qmake";

                // Stage 1
                if (!m_utilClass.invoke(m_utilClass.projectConfiguration().strSettings["QMake bin path"], qmakeArgs, proj.timeout))
                {
                    m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Error in qmake";
                    emit buildComplete(proj.project.name, false);
                    m_utilClass.writeLog(QString("Build project %1 with target %2: [ERROR: QMAKE ERROR]").arg(proj.project.name, proj.target));
                    break;
                }

                m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Running make";

                // Stage 2
                if (!m_utilClass.invoke(m_utilClass.projectConfiguration().strSettings["Make bin path"], buildArgs, proj.timeout))
                {
                    m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Error in make";
                    emit buildComplete(proj.project.name, false);
                    m_utilClass.writeLog(QString("Build project %1 with target %2: [ERROR: MAKE ERROR]").arg(proj.project.name, proj.target));
                    break;
                }

                QDir::setCurrent(currentDir);

                m_utilClass.logChannel() << "[BUILD MANAGER] [BUILD THREAD] Build complete";

                emit buildComplete(proj.project.name, true);
                m_utilClass.writeLog(QString("Build project %1 with target %2: [SUCCESS]").arg(proj.project.name, proj.target));

                m_startingTask = true;
            }
            buildQueue.clear();
            m_startingTask = false;
        }
    );

    m_utilClass.logChannel() << "[BUILD MANAGER] Build thread created, starting";
    m_pProcessThread->start();

    return m_pProcessThread->isRunning();
}

void BuildManager::poll()
{
    if (!m_pProcessThread)
        return;

    if (m_pProcessThread->isFinished())
        return;

    if (m_pProcessThread->isRunning())
    {
        if (!m_pProcessThread->wait(m_utilClass.projectConfiguration().intSettings["Build timeout"]))
            m_pProcessThread->exit(1);
    }

    m_pProcessThread->deleteLater();
    m_pProcessThread = nullptr;

    m_utilClass.logChannel() << "[BUILD MANAGER] Build thread polled";
}
