#include "projectdirectoryfileinterface.h"

#include "filesearcher.h"
#include "dependencyparser.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

#include <thread>

using namespace FileWork;

struct ProjectDirectoryFileInterface::Impl
{
    std::thread * processThread {nullptr};

    QVector<Project> apps;
    QVector<Project> libs;

    QString currentBasePath;

    FileSearcher m_searcher{ apps, libs };
    DependencyParser m_depParser { apps, libs };

    void DEBUG_PRINT_FILES()
    {
        int currentIteration = 1;
        qDebug() << "--------------------------------------------------------------------------------------------------------";
        qDebug() << "[\033[34mDEBUG\033[0m] \033[32mFound apps:\033[0m";
        for (Project & app : apps)
        {
            qDebug() << "\033[33mAPP N:" << currentIteration++ << "\033[0m"   << endl
                     << "NAME:  " << app.name                                 << endl
                     << "SRC:   " << app.srcFilePath                          << endl
                     << "DEPS:  " << app.dependFilePath                       << endl
                     << "DEPON: " << app.depends.join(", ")                   << endl
                        ;
        }

        qDebug() << "--------------------------------------------------------------------------------------------------------";

        currentIteration = 1;
        qDebug() << "[\033[34mDEBUG\033[0m] \033[32mFound libraries:\033[0m";
        for (Project & lib : libs)
        {
            qDebug() << "\033[33mLIBRARY N:" << currentIteration++ << "\033[0m" << endl
                     << "NAME:" << lib.name                                     << endl
                     << "SRC: " << lib.srcFilePath                              << endl
                     << "DEPS:" << lib.dependFilePath                           << endl
                     << "USE: " << lib.useFilePath
                        ;
        }
        qDebug() << "--------------------------------------------------------------------------------------------------------";
    }

    void DEBUG_ADD_DEPENDS()
    {
        qsrand(std::time(NULL));
        QString anotherDepName;
        for (Project & app : apps)
        {
            for (int i = 0; i < 3; i++)
            {
                anotherDepName = libs[ qrand() % libs.size() ].name;
                if (!app.depends.contains(anotherDepName))
                {
                    qDebug() << "[\033[34mDEBUG\033[0m] Adding depend on" << anotherDepName << "for" << app.name;
                    app.depends << anotherDepName;
                }
            }
        }

        updateDepends();
    }

    void setPath(const QString & path)
    {
        m_searcher.setPath(path);
        m_depParser.setPath(path);
    }

    void updateDepends()
    {
        qDebug() << "[UPDATING DEPENDS]";
        for (Project & app : apps)
        {
            std::sort(app.depends.begin(), app.depends.end(),
                [](QString & first, QString & second)
                {
                    return std::lexicographical_compare( first.begin(), first.end(), second.begin(), second.end() );
                }
            );
        }

        for (Project & lib : libs)
        {
            std::sort(lib.depends.begin(), lib.depends.end(),
                [](QString & first, QString & second)
                {
                    return std::lexicographical_compare( first.begin(), first.end(), second.begin(), second.end() );
                }
            );
        }
        qDebug() << "[DEPENDS UPDATED]";
    }
};

ProjectDirectoryFileInterface::ProjectDirectoryFileInterface() :
    m_pImpl {new Impl}
{

}

ProjectDirectoryFileInterface::~ProjectDirectoryFileInterface()
{
    poll();
}

int ProjectDirectoryFileInterface::searchForFiles(const QString path)
{
    if (m_pImpl->processThread)
    {
        return 0;
    }

    m_pImpl->setPath(path);

    m_pImpl->processThread = new std::thread(
        [this]()
        {
            m_pImpl->m_searcher.findFiles();
            m_pImpl->m_depParser.parseAllDepends();
            // m_pImpl->DEBUG_ADD_DEPENDS();
            m_pImpl->DEBUG_PRINT_FILES();
        }
    );

    poll();

    return (m_pImpl->apps.size() + m_pImpl->libs.size());
}

QString ProjectDirectoryFileInterface::currentBasePath() const
{
    return m_pImpl->m_searcher.basePath();
}

QStringList ProjectDirectoryFileInterface::getLibraryNameList()
{
    QStringList result;
    for (const Project & lib : m_pImpl->libs)
    {
        result << lib.name;
    }
    return result;
}

QStringList ProjectDirectoryFileInterface::getAppNameList()
{
    QStringList result;
    for (const Project & app : m_pImpl->apps)
    {
        result << app.name;
    }
    return result;
}

void ProjectDirectoryFileInterface::addLibrary(const QString &appName, const QString &libraryName)
{
    auto appPos = std::find_if(m_pImpl->apps.begin(), m_pImpl->apps.end(), [&appName](Project & app){ return (app.name == appName); });

    auto libraryPos = std::find_if(m_pImpl->libs.begin(), m_pImpl->libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if ((appPos == m_pImpl->apps.end()) || (libraryPos == m_pImpl->libs.end()))
    {
        qDebug() << "[Add dep: \033[31mApp or library not found\033[0m]: " << appName << "<-->" << libraryName;
        return;
    }

    appPos->depends << libraryName;

    m_pImpl->updateDepends();
    qDebug() << "[Dependency \033[32madded\033[0m]: " << appName << "--->" << libraryName;
}

void ProjectDirectoryFileInterface::removeLibrary(const QString &appName, const QString &libraryName)
{
    auto appPos = std::find_if(m_pImpl->apps.begin(), m_pImpl->apps.end(), [&appName](Project & app){ return (app.name == appName); });

    auto libraryPos = std::find_if(m_pImpl->libs.begin(), m_pImpl->libs.end(), [&libraryName](Project & libs){ return (libs.name == libraryName); });

    if ((appPos == m_pImpl->apps.end()) || (libraryPos == m_pImpl->libs.end()))
    {
        qDebug() << "[Remove dep: \033[31mApp or library not found\033[0m]: " << appName << "<-->" << libraryName;
        return;
    }

    appPos->depends.removeOne(libraryName);

    m_pImpl->updateDepends();
    qDebug() << "[Dependency \033[32mremoved\033[0m]: " << appName << "-X->" << libraryName;
}

QStringList ProjectDirectoryFileInterface::getDepends(const QString &appName)
{
    auto app = std::find_if( m_pImpl->apps.begin(), m_pImpl->apps.end(), [&appName](const Project & currentApp){ return (appName == currentApp.name); } );

    if (app != m_pImpl->apps.end())
    {
        return app->depends;
    }
    return QStringList();
}

void ProjectDirectoryFileInterface::poll()
{
    if (m_pImpl->processThread)
    {
        if (m_pImpl->processThread->joinable())
            m_pImpl->processThread->join();
        delete m_pImpl->processThread;
        m_pImpl->processThread = nullptr;
    }
}
