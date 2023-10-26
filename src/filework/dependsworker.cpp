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


void DependsWorker::addLibrary(const QString &projectName, const QString &libraryName)
{
    poll();

    auto projectPos = std::find_if(apps.begin(), apps.end(), [&projectName](Project & app){ return (app.name == projectName); });

    if (projectPos == apps.end())
    {
        projectPos = std::find_if(libs.begin(), libs.end(), [&projectName](Project & app){ return (app.name == projectName); });

        if (projectPos == libs.end())
            return;
    }

    auto libraryPos = std::find_if(libs.begin(), libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if (libraryPos == libs.end())
        return;

    projectPos->depends << libraryName;

    qDebug() << "[Dependency \033[32madded\033[0m]: " << projectName << "--->" << libraryName;
}

void DependsWorker::removeLibrary(const QString &projectName, const QString &libraryName)
{
    poll();

    auto projectPos = std::find_if(apps.begin(), apps.end(), [&projectName](Project & app){ return (app.name == projectName); });

    if (projectPos == apps.end())
    {
        projectPos = std::find_if(libs.begin(), libs.end(), [&projectName](Project & app){ return (app.name == projectName); });

        if (projectPos == libs.end())
            return;
    }

    auto libraryPos = std::find_if(libs.begin(), libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if (libraryPos == libs.end())
        return;

    projectPos->depends.removeOne(libraryName);

    qDebug() << "[Dependency \033[31mremoved\033[0m]: " << projectName << "-X->" << libraryName;
}

QStringList DependsWorker::getDepends(const QString &projectName)
{
    poll();

    auto lib = std::find_if( libs.begin(), libs.end(), [&projectName](const Project & currentProject){ return (projectName == currentProject.name); } );

    if (lib != libs.end())
        return lib->depends;

    auto app = std::find_if( apps.begin(), apps.end(), [&projectName](const Project & currentProject){ return (projectName == currentProject.name); } );

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
            processPercent.store(0);
            float progressPart = (float)(apps.size() + libs.size()) / 100.0f;

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
                processPercent.store(processPercent.load() + progressPart);
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
                processPercent.store(processPercent.load() + progressPart);
            }
            qDebug() << "[DEPENDS WORKER] Depends updated";
            processPercent.store(100);
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

void DependsWorker::saveChanges()
{
    poll();
    processThread = new std::thread(
        [this]()
        {
            processPercent.store(0);
            float progressPart = (float)(apps.size() + libs.size()) / 100.0f;

            qDebug() << "[DEPENDS WORKER] Saving changes";
            for (Project & app : apps)
            {
                m_depParser.writeDepends(app);
                processPercent.store(processPercent.load() + progressPart);
            }

            for (Project & lib : libs)
            {
                m_depParser.writeDepends(lib);
                processPercent.store(processPercent.load() + progressPart);
            }
            qDebug() << "[DEPENDS WORKER] Saving complete";
            processPercent.store(100);
    });
}

int DependsWorker::progressPercent() const
{
    return processPercent.load();
}
