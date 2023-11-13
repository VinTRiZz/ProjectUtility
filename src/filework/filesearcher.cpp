#include "filesearcher.h"
#include "projectsettings.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

using namespace FileWork;

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
    QDir projectDir;

    QStringList entries = searchDir.entryList();
    entries.removeOne(".");
    entries.removeOne("..");

    Project foundProj;
    foundProj.isLibrary = isLibs;

    int projectFilePos = -1;
    QStringList projectContents;
    for (QString & entry : entries)
    {
        foundProj.name = entry;

        projectDir.setPath( searchDir.absoluteFilePath(entry) );
        projectContents = projectDir.entryList();

        projectFilePos = projectContents.indexOf(entry + ".pro");

        if (projectFilePos > 0)
            foundProj.projectProFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        projectFilePos = projectContents.indexOf("deps.pri");

        if (projectFilePos > 0)
            foundProj.dependFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        if (isLibs)
        {
            projectFilePos = projectContents.indexOf("use.pri");

            if (projectFilePos > 0)
                foundProj.useFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));
        }

        if (!isLibs)
            apps.push_back(foundProj);
        else
            libs.push_back(foundProj);
    }

    return (((apps.size() > 0) && !isLibs) || ((libs.size() > 0) && isLibs));
}

//bool FileSearcher::searchForFiles(const QString &basePath)
//{
//    QStringList findArgs;
//    findArgs << basePath << "-name" << "*.pri";

//    QProcess findProcess;

//    findProcess.setProgram("find");
//    findProcess.setArguments(findArgs);

//    findProcess.start();
//    if (!findProcess.waitForStarted(FIND_START_TIMEOUT))
//    {
//        qDebug() << "[FILE SEARCHER] [\033[31mFIND\033[0m] Start error, args:"  << findArgs.join(" ");
//        return false;
//    }

//    if (!findProcess.waitForFinished(FIND_FINISH_TIMEOUT))
//    {
//        qDebug() << "[FILE SEARCHER] [\033[31mFIND\033[0m] Finish error, args:" << findArgs.join(" ");
//        return false;
//    }

//    findOutput = findProcess.readAllStandardOutput();

//    if (findOutput.size() < 1)
//    {
//        qDebug() << "[FILE SEARCHER] [\033[31mFIND\033[0m] No files found, args:"  << findArgs.join(" ");
//        return false;
//    }

//    return true;
//}

void FileSearcher::findFiles()
{
    const QString
            appDirBasePath = currentBasePath + Configuration::mainProjectConfiguration.appDirectory,
            libDirBasePath = currentBasePath + Configuration::mainProjectConfiguration.libraryDirectory
            ;

    apps.clear();
    libs.clear();

    if (!searchForProjects(appDirBasePath, false) || !searchForProjects(libDirBasePath, true))
    {
        qDebug() << "[FILE SEARCHER] [\033[31mNot found projects of apps or libraries\033[0m]";
        return;
    }

    std::sort(apps.begin(), apps.end(), [](Project & proj_1, Project & proj_2){ return (proj_1.name > proj_2.name); });
    std::sort(libs.begin(), libs.end(), [](Project & proj_1, Project & proj_2){ return (proj_1.name > proj_2.name); });

//    int copyFrom, copyTo;
//    QString buffer;
//    for (Project & app : apps)
//    {
//        if (!searchForFiles(appDirBasePath + "/" + app.name))
//            continue;

//        copyFrom = 0;
//        copyTo = 0;
//        for (; copyTo < findOutput.size(); copyTo++)
//        {
//            copyTo = findOutput.indexOf(QChar(0x0A), copyFrom);
//            if (copyTo != copyFrom)
//            {
//                buffer.clear();
//                buffer.resize(copyTo - copyFrom);
//                std::copy(findOutput.data() + copyFrom, findOutput.data() + copyTo, buffer.begin());
//                copyFrom = copyTo + 1;

//                if (buffer.contains("deps.pri"))
//                {
//                    app.dependFilePath = buffer;
//                } else if (buffer.contains("use.pri"))
//                {
//                    app.useFilePath = buffer;
//                }
//            }
//        }
//    }

//    for (Project & lib : libs)
//    {
//        if (!searchForFiles(libDirBasePath + "/" + lib.name))
//            continue;

//        copyFrom = 0;
//        copyTo = 0;
//        for (; copyTo < findOutput.size(); copyTo++)
//        {
//            copyTo = findOutput.indexOf(QChar(0x0A), copyFrom);
//            if (copyTo != copyFrom)
//            {
//                buffer.clear();
//                buffer.resize(copyTo - copyFrom);
//                std::copy(findOutput.data() + copyFrom, findOutput.data() + copyTo, buffer.begin());
//                copyFrom = copyTo + 1;

//                if (buffer.contains("deps.pri"))
//                {
//                    lib.dependFilePath = buffer;
//                } else if (buffer.contains("use.pri"))
//                {
//                    lib.useFilePath = buffer;
//                }
//            }
//        }
//    }
}
