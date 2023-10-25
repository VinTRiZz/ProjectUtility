#include "filesearcher.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

using namespace FileWork;

#define FIND_START_TIMEOUT 1000
#define FIND_FINISH_TIMEOUT 10000

#define LIBRARY_PROJECTS_BASE_DIRECTORY "/Libraries"
#define APP_PROJECTS_BASE_DIRECTORY     "/Apps"
#define LIBRARIES_BASE_DIRECTORY        "/LIB"

FileSearcher::FileSearcher(QVector<Project> & apps, QVector<Project> & libs):
    apps{apps}, libs{libs}
{

}

FileSearcher::~FileSearcher()
{

}

void FileSearcher::setPath(const QString &path)
{
    currentBasePath = path;
}

QString FileSearcher::basePath() const
{
    return currentBasePath;
}

bool FileSearcher::searchForProjects(const QString &basePath, bool isLibs)
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

bool FileSearcher::searchForFiles(const QString &basePath)
{
    QStringList findArgs;
    findArgs << basePath << "-name" << "*.pri";

    QProcess findProcess;

    findProcess.setProgram("find");
    findProcess.setArguments(findArgs);

    findProcess.start();
    if (!findProcess.waitForStarted(FIND_START_TIMEOUT))
    {
        qDebug() << "[FILE SEARCHER] [\033[31mFIND\033[0m] Start error, args:"  << findArgs.join(" ");
        return false;
    }

    if (!findProcess.waitForFinished(FIND_FINISH_TIMEOUT))
    {
        qDebug() << "[FILE SEARCHER] [\033[31mFIND\033[0m] Finish error, args:" << findArgs.join(" ");
        return false;
    }

    findOutput = findProcess.readAllStandardOutput();

    if (findOutput.size() < 1)
    {
        qDebug() << "[FILE SEARCHER] [\033[31mFIND\033[0m] No files found, args:"  << findArgs.join(" ");
        return false;
    }

    return true;
}

void FileSearcher::findFiles()
{
    const QString
            appDirBasePath = currentBasePath + APP_PROJECTS_BASE_DIRECTORY,
            libDirBasePath = currentBasePath + LIBRARY_PROJECTS_BASE_DIRECTORY
            ;

    if (!searchForProjects(appDirBasePath, false) || !searchForProjects(libDirBasePath, true))
    {
        qDebug() << "[FILE SEARCHER] [\033[31mNot found projects of apps or libraries\033[0m]";
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
