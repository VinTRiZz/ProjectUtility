#include "filesearcher.h"
#include "projectsettings.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QVector>

using namespace DependsSearcher;

FileSearcher::FileSearcher(QVector<Project> & apps, QVector<Project> & libs, UtilFunctionClass & utilClass):
    apps{apps}, libs{libs}, m_utilClass {utilClass}
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

bool FileSearcher::searchForProjects(const QString &basePath)
{
    qDebug() << "[FILE SEARCHER] Searching in directory:" << basePath;
    QDir searchDir(basePath);
    QDir projectDir;

    QStringList entries = searchDir.entryList();
    entries.removeOne(".");
    entries.removeOne("..");

    int projectFilePos = -1;
    bool isLib {false};
    QStringList projectContents;
    for (QString & entry : entries)
    {
        Project foundProj;

        foundProj.name = entry;

        if (!QFileInfo(searchDir.absoluteFilePath(entry)).isDir())
            continue;

        projectDir.setPath( searchDir.absoluteFilePath(entry) );
        projectContents = projectDir.entryList();

        projectFilePos = projectContents.indexOf(entry + ".pro");

        if (projectFilePos >= 0)
            foundProj.projectProFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        if (foundProj.projectProFilePath.isEmpty())
        {
            qDebug() << "[FILE SEARCHER] Not a project directory:" << entry;
            continue;
        }

        projectFilePos = projectContents.indexOf("deps.pri");

        if (projectFilePos >= 0)
            foundProj.dependFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        projectFilePos = projectContents.indexOf("use.pri");

        if (projectFilePos >= 0)
            foundProj.useFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        projectFilePos = projectContents.indexOf("include");

        isLib = (projectFilePos >= 0);
        foundProj.isLibrary = isLib;

        if (!isLib)
            apps.push_back(foundProj);
        else
            libs.push_back(foundProj);
    }

    return (apps.size() > 0) || (libs.size() > 0);
}

void FileSearcher::parseFindOutput()
{
    qDebug() << "[FILE SEARCHER] Started parsing find output";
    apps.clear();
    libs.clear();

    QDir projectDir;
    QStringList projectContents;
    int projectFilePos = -1;
    bool isLib {false};

    for (const QString & proFile : filesFound)
    {
        Project foundProj;

        projectDir.setPath( QFileInfo(proFile).absolutePath() );
        projectContents = projectDir.entryList();

        foundProj.name = projectDir.dirName();
        foundProj.projectProFilePath = proFile;

        qDebug() << "[FILE SEARCHER] Found project:" << foundProj.name;

        projectFilePos = projectContents.indexOf("deps.pri");

        if (projectFilePos >= 0)
            foundProj.dependFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        projectFilePos = projectContents.indexOf("use.pri");

        if (projectFilePos >= 0)
            foundProj.useFilePath = projectDir.absoluteFilePath(projectContents.at(projectFilePos));

        projectFilePos = projectContents.indexOf("include");

        isLib = (projectFilePos >= 0);
        foundProj.isLibrary = isLib;

        if (!isLib)
            apps.push_back(foundProj);
        else
            libs.push_back(foundProj);
    }

    qDebug() << "[FILE SEARCHER] Projects replaced";
}

void FileSearcher::findProjectFiles()
{
    findOutput.clear();
    filesFound.clear();

    QStringList findArgs;
    findArgs << currentBasePath << "-name" << "*.pro";
    if (!m_utilClass.invoke("find", findArgs, findOutput, m_utilClass.projectConfiguration().intSettings["Find files timeout"]))
        return;

    QString anotherFile;
    for (const QChar s : findOutput)
    {
        if (s != '\n')
            anotherFile += s;
        else
        {
            filesFound << anotherFile;
            anotherFile.clear();
        }
    }

    qDebug() << "[FILE SEARCHER] Found" << filesFound.size() << "files";
}

void FileSearcher::findFiles()
{
//    searchForProjects(currentBasePath + "/App");
//    searchForProjects(currentBasePath + "/Libraries");

    findProjectFiles();
    parseFindOutput();

    std::sort(apps.begin(), apps.end(), [](Project & proj_1, Project & proj_2){ return (proj_1.name > proj_2.name); });
    std::sort(libs.begin(), libs.end(), [](Project & proj_1, Project & proj_2){ return (proj_1.name > proj_2.name); });
}
