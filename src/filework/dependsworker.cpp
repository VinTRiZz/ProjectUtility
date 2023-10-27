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


void DependsWorker::addLibrary(Project * proj, const QString &libraryName)
{
    poll();

    auto libraryPos = std::find_if(libs.begin(), libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if (libraryPos == libs.end())
        return;

    proj->depends << libraryName;

    qDebug() << "[Dependency \033[32madded\033[0m]: " << proj->name << "--->" << libraryName;
}

void DependsWorker::removeLibrary(Project * proj, const QString &libraryName)
{
    poll();

    proj->depends.removeOne(libraryName);

    qDebug() << "[Dependency \033[31mremoved\033[0m]: " << proj->name << "-X->" << libraryName;
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
