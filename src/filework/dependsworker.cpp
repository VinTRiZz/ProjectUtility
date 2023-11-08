#include "dependsworker.h"

#include <QDebug>

using namespace FileWork;

DependsWorker::DependsWorker(QVector<Project> & apps, QVector<Project> & libs):
    apps{apps}, libs{libs}, m_depParser { apps, libs },
    m_utilClass( UtilFunctionClass::getInstance(&apps, &libs) )
{

}

DependsWorker::~DependsWorker()
{
    poll();
}


bool DependsWorker::addLibrary(Project * proj, const QString &libraryName)
{
    poll();

    bool libraryExist = false;
    for (const Project & lib : libs)
    {
        libraryExist = (lib.name == libraryName);
        if (libraryExist)
            break;
    }
    if (!libraryExist)
        return false;

    proj->depends << libraryName;

    QStringList dependQuery;
    if (m_utilClass.hasRecurseDepend(dependQuery, proj))
    {
        qDebug() << "[DEPENDS WORKER] Found recursive in project" << proj->name << "depends:" << dependQuery.join("-->");
        proj->depends.removeOne(libraryName);
        return false;
    }

    qDebug() << "[DEPENDS WORKER] [\033[32mAdded\033[0m]: " << proj->name << "--->" << libraryName;
    return true;
}

void DependsWorker::removeLibrary(Project * proj, const QString &libraryName)
{
    poll();
    proj->depends.removeOne(libraryName);
    qDebug() << "[DEPENDS WORKER] [\033[31mRemoved\033[0m]: " << proj->name << "-X->" << libraryName;
}

void DependsWorker::updateDepends()
{
    poll();
    processThread = new std::thread(
        [this]()
        {
            m_utilClass.setPercent(0);
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
                m_utilClass.increasePercent(progressPart);
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
                m_utilClass.increasePercent(progressPart);
            }
            qDebug() << "[DEPENDS WORKER] Depends updated";
            m_utilClass.setPercent(100);
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
            m_utilClass.setPercent(0);
            float progressPart = (float)(apps.size() + libs.size()) / 100.0f;

            qDebug() << "[DEPENDS WORKER] Saving changes";
            for (Project & app : apps)
            {
                m_depParser.writeDepends(app);
                m_utilClass.increasePercent(progressPart);
            }

            for (Project & lib : libs)
            {
                m_depParser.writeDepends(lib);
                m_utilClass.increasePercent(progressPart);
            }
            qDebug() << "[DEPENDS WORKER] Saving complete";
            m_utilClass.setPercent(100);
    });
}
