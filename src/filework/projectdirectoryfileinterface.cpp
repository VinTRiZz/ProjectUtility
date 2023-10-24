#include "projectdirectoryfileinterface.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

#include <thread>

#define FIND_START_TIMEOUT 1000
#define FIND_FINISH_TIMEOUT 10000

#define LIBRARY_PROJECTS_BASE_DIRECTORY "/Libraries"
#define APP_PROJECTS_BASE_DIRECTORY     "/Apps"
#define LIBRARIES_BASE_DIRECTORY        "/LIB"

using namespace FileWork;

struct Project
{
    bool isLibrary {false};
    QString name;
    QString dependFilePath;
    QString useFilePath;
    QString srcFilePath;
    QStringList depends;
};

struct ProjectDirectoryFileInterface::Impl
{
    QString currentBasePath;
    std::thread * processThread {nullptr};
    QString findOutput;
    QVector<Project> apps;
    QVector<Project> libs;

    bool searchForProjects(const QString & basePath, bool isLibs)
    {
        QDir searchDir(basePath);

        QStringList entries = searchDir.entryList();
        entries.removeOne(".");
        entries.removeOne("..");

        Project foundProj;
        foundProj.isLibrary = isLibs;

        if (!isLibs)
            apps.clear();
        else
            libs.clear();

        for (QString & entry : entries)
        {
            foundProj.name = entry;
            if (!isLibs)
                apps.push_back(foundProj);
            else
                libs.push_back(foundProj);
        }

        return (((apps.size() > 0) && !isLibs) || ((libs.size() > 0) && isLibs));
    }



    bool searchForFiles(const QString & basePath)
    {
        QStringList findArgs;
        findArgs << basePath << "-name" << "*.pri";

        QProcess findProcess;

        findProcess.setProgram("find");
        findProcess.setArguments(findArgs);

        findProcess.start();
        if (!findProcess.waitForStarted(FIND_START_TIMEOUT))
        {
            qDebug() << "[\033[31mFIND\033[0m] Start error, args:"  << findArgs.join(" ");
            return false;
        }

        if (!findProcess.waitForFinished(FIND_FINISH_TIMEOUT))
        {
            qDebug() << "[\033[31mFIND\033[0m] Finish error, args:" << findArgs.join(" ");
            return false;
        }

        findOutput = findProcess.readAllStandardOutput();

        if (findOutput.size() < 1)
        {
            qDebug() << "[\033[31mFIND\033[0m] No files found, args:"  << findArgs.join(" ");
            return false;
        }

        return true;
    }



    void findFiles()
    {
        const QString
                appDirBasePath = currentBasePath + APP_PROJECTS_BASE_DIRECTORY,
                libDirBasePath = currentBasePath + LIBRARY_PROJECTS_BASE_DIRECTORY
        ;

        if (!searchForProjects(appDirBasePath, false) || !searchForProjects(libDirBasePath, true))
        {
            qDebug() << "[\033[31mNot found projects of apps or libraries\033[0m]";
            return;
        }

        int copyFrom, copyTo;
        QString buffer;
        for (Project & app : apps)
        {
            if (!searchForFiles(appDirBasePath + "/" + app.name))
                continue;

            copyFrom = 0;
            copyTo = 0;
            for (; copyTo < findOutput.size(); copyTo++)
            {
                copyTo = findOutput.indexOf(QChar(0x0A), copyFrom);
                if (copyTo != copyFrom)
                {
                    buffer.clear();
                    buffer.resize(copyTo - copyFrom);
                    std::copy(findOutput.data() + copyFrom, findOutput.data() + copyTo, buffer.begin());
                    copyFrom = copyTo + 1;

                    if (buffer.contains("deps.pri"))
                    {
                        app.dependFilePath = buffer;
                    } else if (buffer.contains("use.pri"))
                    {
                        app.useFilePath = buffer;
                    } else if (buffer.contains("src.pri"))
                    {
                        app.srcFilePath = buffer;
                    }
                }
            }
        }

        for (Project & lib : libs)
        {
            if (!searchForFiles(libDirBasePath + "/" + lib.name))
                continue;

            copyFrom = 0;
            copyTo = 0;
            for (; copyTo < findOutput.size(); copyTo++)
            {
                copyTo = findOutput.indexOf(QChar(0x0A), copyFrom);
                if (copyTo != copyFrom)
                {
                    buffer.clear();
                    buffer.resize(copyTo - copyFrom);
                    std::copy(findOutput.data() + copyFrom, findOutput.data() + copyTo, buffer.begin());
                    copyFrom = copyTo + 1;

                    if (buffer.contains("deps.pri"))
                    {
                        lib.dependFilePath = buffer;
                    } else if (buffer.contains("use.pri"))
                    {
                        lib.useFilePath = buffer;
                    } else if (buffer.contains("src.pri"))
                    {
                        lib.srcFilePath = buffer;
                    }
                }
            }
        }
    }

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
        QString anotherDepName;
        for (Project & app : apps)
        {
            for (int i = 0; i < (qrand() % (libs.size() - 1) + 1); i++)
            {
                anotherDepName = libs[qrand() % libs.size()].name;
                qDebug() << "[\033[34mDEBUG\033[0m] Adding depend on" << anotherDepName << "for" << app.name;
                if (!app.depends.contains(anotherDepName))
                    app.depends << anotherDepName;
            }
        }
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

    m_pImpl->currentBasePath = path;

    m_pImpl->processThread = new std::thread(
        [this]()
        {
            m_pImpl->findFiles();
            m_pImpl->DEBUG_ADD_DEPENDS();
            // m_pImpl->DEBUG_PRINT_FILES();
        }
    );

    poll();

    return m_pImpl->apps.size() + m_pImpl->libs.size();
}

QString ProjectDirectoryFileInterface::currentBasePath() const
{
    return m_pImpl->currentBasePath;
}

QStringList ProjectDirectoryFileInterface::getLibraryNameList()
{
    QStringList result;
    for (Project & lib : m_pImpl->libs)
    {
        result << lib.name;
    }
    return result;
}

QStringList ProjectDirectoryFileInterface::getAppNameList()
{
    QStringList result;
    for (Project & app : m_pImpl->apps)
    {
        result << app.name;
    }
    return result;
}

void ProjectDirectoryFileInterface::addLibrary(const QString &appName, const QString &libraryName)
{
    qDebug() << "\033[32mAdding library" << libraryName << "to project:" << appName << "\033[0m";
}

void ProjectDirectoryFileInterface::removeLibrary(const QString &appName, const QString &libraryName)
{
    qDebug() << "\033[33mRemoving library" << libraryName << "from project:" << appName << "\033[0m";
}

QStringList ProjectDirectoryFileInterface::getDepends(const QString &appName)
{
    auto app = std::find_if( m_pImpl->apps.begin(), m_pImpl->apps.end(), [&appName](const Project & app){ return (appName == app.name); } );

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
