#include "dependsworker.h"

#include <QDebug>

using namespace FileWork;

DependsWorker::DependsWorker(QVector<Project> & apps, QVector<Project> & libs):
    apps{apps}, libs{libs}, m_depParser { apps, libs }
{

}

DependsWorker::~DependsWorker()
{
    poll();
}


void DependsWorker::addLibrary(const QString &appName, const QString &libraryName)
{
    poll();

    auto appPos = std::find_if(apps.begin(), apps.end(), [&appName](Project & app){ return (app.name == appName); });

    auto libraryPos = std::find_if(libs.begin(), libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if ((appPos == apps.end()) || (libraryPos == libs.end()))
        return;

    appPos->depends << libraryName;

    updateDepends();
    qDebug() << "[Dependency \033[32madded\033[0m]: " << appName << "--->" << libraryName;
}

void DependsWorker::removeLibrary(const QString &appName, const QString &libraryName)
{
    poll();

    auto appPos = std::find_if(apps.begin(), apps.end(), [&appName](Project & app){ return (app.name == appName); });

    auto libraryPos = std::find_if(libs.begin(), libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if ((appPos == apps.end()) || (libraryPos == libs.end()))
        return;

    appPos->depends.removeOne(libraryName);

    updateDepends();
    qDebug() << "[Dependency \033[31mremoved\033[0m]: " << appName << "-X->" << libraryName;
}

QStringList DependsWorker::getDepends(const QString &appName)
{
    poll();

    auto app = std::find_if( apps.begin(), apps.end(), [&appName](const Project & currentApp){ return (appName == currentApp.name); } );

    if (app != apps.end())
        return app->depends;

    return QStringList();
}

void DependsWorker::updateDepends()
{
    poll();
    processThread = new std::thread(
                [this]()
    {
        qDebug() << "[DEPENDS WORKER] Updating depends";

        QStringList dependsBuffer;

        for (Project & app : apps)
        {
            dependsBuffer = app.depends;
            std::sort(dependsBuffer.begin(), dependsBuffer.end(),
                      [](QString & first, QString & second)
            {
                return std::lexicographical_compare( first.begin(), first.end(), second.begin(), second.end() );
            }
            );
            m_depParser.writeDepends(app);
        }

        for (Project & lib : libs)
        {
            std::sort(lib.depends.begin(), lib.depends.end(),
                      [](QString & first, QString & second)
            {
                return std::lexicographical_compare( first.begin(), first.end(), second.begin(), second.end() );
            }
            );
            m_depParser.writeDepends(lib);
        }
        qDebug() << "[DEPENDS WORKER] Depends updated";
    }
    );
}

void DependsWorker::poll()
{
    if (processThread)
    {
        if (processThread->joinable())
            processThread->join();
        delete processThread;
        processThread = nullptr;
    }
}

void DependsWorker::setPath(const QString &path)
{
    currentDirectory = path;
    m_depParser.setPath(path);
}

void DependsWorker::parseFiles()
{
    m_depParser.parseAllDepends();
}

void DependsWorker::setupDependsFromFiles(Project &proj)
{
    m_depParser.parseDepends(proj);
}
