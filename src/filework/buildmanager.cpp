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
    while (m_startingTask);

    m_startingTask = true;
    buildQueue.push_back(proj);
    m_startingTask = false;

    return true;
}

bool BuildManager::rebuild(const BuildProjectHandle & proj)
{
    m_utilClass.writeLog("Project rebuild started");

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.project->projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList cleanArgs;
    cleanArgs << "clean";

    QDir::setCurrent(projectDir);
    m_utilClass.invoke("/usr/bin/make", cleanArgs, proj.timeout);
    QDir::setCurrent(currentDir);

    return build(proj);
}

bool BuildManager::startBuilding()
{
    poll();

    m_pProcessThread = QThread::create(
        [this]()
        {
            BuildProjectHandle proj;

            m_startingTask = true;
            while (buildQueue.size())
            {
                while (m_startingTask);

                m_startingTask = true;
                proj = buildQueue.first();
                buildQueue.pop_front();
                m_startingTask = false;

                m_utilClass.writeLog(QString("Project build \"%1\" with target \"%2\" started").arg(proj.project->name, proj.target).toUtf8());

                const QString currentDir = QDir::currentPath();
                const QString projectDir = QFileInfo(proj.project->projectProFilePath).absolutePath();

                QDir::setCurrent(projectDir);

                QStringList qmakeArgs;
                qmakeArgs << proj.project->name + ".pro" << "\-spec" << "linux\-g\+\+";

                if (proj.target == "debug")
                    qmakeArgs << "CONFIG+=debug CONFIG+=qml_debug";
                else if (proj.target == "release")
                    qmakeArgs << "CONFIG+=qtquickcompiler";
                else
                {
                    qDebug() << "[BUILD MANAGER] No target selected";
                    m_utilClass.writeLog("No target selected");
                    emit buildComplete(proj.project->name, false);
                    continue;
                }

                QStringList buildArgs;

                // Stage 1
                if (!m_utilClass.invoke("/usr/bin/qmake", qmakeArgs, proj.timeout))
                {
                    emit buildComplete(proj.project->name, false);
                    continue;
                }

                // Stage 2
                if (!m_utilClass.invoke("/usr/bin/make", buildArgs, proj.timeout))
                {
                    emit buildComplete(proj.project->name, false);
                    continue;
                }

                QDir::setCurrent(currentDir);

                emit buildComplete(proj.project->name, true);
            }
        }
    );

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
}
