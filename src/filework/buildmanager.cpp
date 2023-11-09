#include "buildmanager.h"

#include <QDebug>
#include <QDir>
#include <QThread>

using namespace FileWork;

BuildManager::BuildManager(QObject * parent) :
    QObject(parent),
    m_utilClass (m_utilClass.getInstance())
{

}

BuildManager::~BuildManager()
{
    poll();
}

bool BuildManager::build(const BuildProjectHandle & proj)
{
    qDebug() << "[BUILD MANAGER] Adding task:" << proj.project.name << "with target" << proj.target;
    while (m_startingTask);

    m_startingTask = true;
    buildQueue.push_back(proj);
    m_startingTask = false;

    qDebug() << "[BUILD MANAGER] Task add complete";
    return true;
}

bool BuildManager::rebuild(const BuildProjectHandle & proj)
{
    qDebug() << "[BUILD MANAGER] Cleaning build";

    m_utilClass.writeLog("Project rebuild started");

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.project.projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList cleanArgs;
    cleanArgs << "clean";

    QDir::setCurrent(projectDir);
    m_utilClass.invoke("/usr/bin/make", cleanArgs, proj.timeout);
    QDir::setCurrent(currentDir);

    qDebug() << "[BUILD MANAGER] Build cleaned";
    return build(proj);
}

bool BuildManager::startBuilding()
{
    poll();
    qDebug() << "[BUILD MANAGER] Build thread creating";

    m_pProcessThread = QThread::create(
        [this]()
        {
            qDebug() << "[BUILD MANAGER] [BUILD THREAD] Created";

            BuildProjectHandle proj;

            m_startingTask = true;
            while (buildQueue.size())
            {
                m_startingTask = false;

                qDebug() << "[BUILD MANAGER] [BUILD THREAD] Asking for project";

                while (m_startingTask);

                m_startingTask = true;
                proj = buildQueue.first();
                buildQueue.pop_front();
                m_startingTask = false;

                qDebug() << "[BUILD MANAGER] [BUILD THREAD] Building project:" << proj.project.name << "with target" << proj.target;

                m_utilClass.writeLog(QString("Project build \"%1\" with target \"%2\" started").arg(proj.project.name, proj.target).toUtf8());

                const QString currentDir = QDir::currentPath();
                const QString projectDir = QFileInfo(proj.project.projectProFilePath).absolutePath();

                QDir::setCurrent(projectDir);

                QStringList qmakeArgs;
                qmakeArgs << proj.project.name + ".pro" << "\-spec" << "linux\-g\+\+";

                if (proj.target == "debug")
                    qmakeArgs << "CONFIG+=debug CONFIG+=qml_debug";
                else if (proj.target == "release")
                    qmakeArgs << "CONFIG+=qtquickcompiler";
                else
                {
                    qDebug() << "[BUILD MANAGER] [BUILD THREAD] No target selected, skipped";
                    m_utilClass.writeLog("No target selected, skipped");
                    emit buildComplete(proj.project.name, false);
                    continue;
                }

                QStringList buildArgs;

                qDebug() << "[BUILD MANAGER] [BUILD THREAD] Running qmake";

                // Stage 1
                if (!m_utilClass.invoke("/usr/bin/qmake", qmakeArgs, proj.timeout))
                {
                    qDebug() << "[BUILD MANAGER] [BUILD THREAD] Error in qmake";
                    emit buildComplete(proj.project.name, false);
                    continue;
                }

                qDebug() << "[BUILD MANAGER] [BUILD THREAD] Running make";

                // Stage 2
                if (!m_utilClass.invoke("/usr/bin/make", buildArgs, proj.timeout))
                {
                    qDebug() << "[BUILD MANAGER] [BUILD THREAD] Error in make";
                    emit buildComplete(proj.project.name, false);
                    continue;
                }

                QDir::setCurrent(currentDir);

                qDebug() << "[BUILD MANAGER] [BUILD THREAD] Build complete";

                emit buildComplete(proj.project.name, true);

                m_startingTask = true;
            }
            m_startingTask = false;
        }
    );

    qDebug() << "[BUILD MANAGER] Build thread created, starting";
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
        if (!m_pProcessThread->wait(BUILD_TIMEOUT))
            m_pProcessThread->exit(1);
    }

    m_pProcessThread->deleteLater();
    m_pProcessThread = nullptr;

    qDebug() << "[BUILD MANAGER] Build thread polled";
}
