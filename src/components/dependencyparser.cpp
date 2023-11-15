#include "dependencyparser.h"

#include "projectsettings.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <QRegularExpressionMatch>

#include <QDebug>

using namespace DependsSearcher;

DependencyParser::DependencyParser(QVector<Project> & apps, QVector<Project> & libs):
    apps{apps}, libs{libs},
    m_utilClass( UtilFunctionClass::getInstance(&apps, &libs) )
{

}

DependencyParser::~DependencyParser()
{

}

void DependencyParser::setPath(const QString &path)
{
    currentBasePath = path;
}

void DependencyParser::parseAllDepends()
{
    qDebug() << "[DEPENDS PARSER] Parsing started";

    QDir::current().cd(currentBasePath);
    if (currentBasePath.size() > 0)
    {
        for (Project & app : apps)
            parseDepends(app);

        for (Project & lib : libs)
            parseDepends(lib);
    }

    qDebug() << "[DEPENDS PARSER] Parsing complete";
}

void DependencyParser::parseDepends(Project &proj)
{
    if (proj.dependFilePath.isEmpty())
    {
        qDebug() << "[DEPENDS PARSER] No depend file specified for project:" << proj.name;
        return;
    }

    qDebug() << "[DEPENDS PARSER] Opening dep file for project:" << proj.name;
    QFile deps(proj.dependFilePath);

    deps.open(QIODevice::ReadOnly);

    if (!deps.isOpen())
    {
        qDebug() << "[DEPENDS PARSER] File not opened with error:" << deps.errorString() << ", path:" << deps.fileName();
        return;
    }

    std::string depsFileContents = deps.readAll().toStdString();

    std::string::iterator includeStartPos    = depsFileContents.begin(),
                          beginBracketPos    = includeStartPos,
                          endBracketPos      = includeStartPos
    ;
    const std::string INCLUDE_STRING = "include";

    QStringList depPaths;
    QString buffer;
    std::string bufferStd;

    while (includeStartPos != depsFileContents.end())
    {
        includeStartPos = std::search(includeStartPos, depsFileContents.end(), INCLUDE_STRING.begin(), INCLUDE_STRING.end());

        if (includeStartPos == depsFileContents.end())
            break;

        beginBracketPos = std::find(includeStartPos, depsFileContents.end(), '(');
        endBracketPos = std::find(beginBracketPos, depsFileContents.end(), ')');

        if (beginBracketPos != endBracketPos)
        {
            bufferStd = std::string(beginBracketPos + 1, endBracketPos);
            buffer = bufferStd.c_str();

            if (buffer.contains("$$PWD"))
            {
                QDir baseDir = QFileInfo(proj.projectProFilePath).absoluteDir();

                const int cdUpCount = std::count_if(bufferStd.begin(), bufferStd.end(), [](auto & s){ return (s == '.') && (*(&s + 1) == '.') && (*(&s + 2) == '/'); });
                buffer.remove(QRegExp("\\$\\$PWD(\\/\\.\\.)+\\/"));
                if (buffer.at(0) != '/')
                    buffer = "/" + buffer;

                if (cdUpCount)
                {
                    QString pwdPath = QFileInfo(proj.projectProFilePath).absolutePath();

                    pwdPath.chop(baseDir.dirName().size() + 1);

                    for (int i = 1; i < cdUpCount; i++)
                    {
                        baseDir.cdUp();
                        pwdPath.chop(baseDir.dirName().size() + 1);
                    }
                    buffer = pwdPath + buffer;
                }
            }

            depPaths << buffer;

            if (!allLibrariesParsed.contains(buffer))
                allLibrariesParsed.push_back(buffer);
        }
        includeStartPos++;
    }

    proj.depends.clear();

    for (QString & dep : depPaths)
    {
        dep.chop(QFileInfo(dep).fileName().size());
        proj.depends << QFileInfo(dep).absoluteDir().dirName();
        qDebug() << "[DEPENDS PARSER] Parsed dep:" << proj.name << "--->" << proj.depends.last();
    }

    std::sort(proj.depends.begin(), proj.depends.end(), [](QString & dep_1, QString & dep_2){ return (dep_2 > dep_1); });
}

void DependencyParser::writeDepends(Project &proj)
{
    qDebug() << "[DEPENDS PARSER] Writing depends for" << proj.name;

    QIODevice::OpenMode openMode = QIODevice::Truncate;

    if (proj.dependFilePath.isEmpty())
    {
        qDebug() << "[DEPENDS PARSER] \033[33mWarning\033[0m No depend file specified for project:" << proj.name;

        if (proj.depends.size() == 0)
            return;

        qDebug() << "[DEPENDS PARSER] Depends file will be created";

        openMode = QIODevice::NewOnly;

        QString proPath = QFileInfo(proj.projectProFilePath).absoluteDir().absolutePath();
        proj.dependFilePath = proPath + "/deps.pri";
    }

    QFile deps(proj.dependFilePath);
    deps.open(openMode | QIODevice::WriteOnly);

    if (!deps.isOpen())
    {
        qDebug() << "[DEPENDS PARSER] \033[31mError\033[0m opening depends file:" << proj.dependFilePath;
        return;
    }

    QStringList dependQuery;
    while (m_utilClass.hasRecurseDepend(dependQuery, &proj))
    {
        qDebug() << "[DEPENDS WORKER] Found recurse in project" << proj.name << "depends:" << dependQuery.join("-->");
        qDebug() << "[DEPENDS WORKER] Removing recursive depend on project:" << dependQuery.last();
        proj.depends.removeOne(dependQuery.last());
        dependQuery.clear();
    }

    QTextStream depsStream(&deps);

    QStringList depList = proj.depends;

    for (QString & dep : depList)
    {
        for (const Project & lib : libs)
        {
            if (lib.name == dep)
            {
                dep = lib.useFilePath;
            }
        }

        if (dep.isEmpty())
        {
            dep = "ABOBA";
        }
    }

    QDir baseDir = QFileInfo(proj.projectProFilePath).absoluteDir();
    QString pwdPath = "$$PWD";

    while ((baseDir.absolutePath() != currentBasePath) && (baseDir.absolutePath() != "/"))
    {
        baseDir.cd("..");
        pwdPath += "/..";
    }

    qDebug() << "Base path for config:" << pwdPath;

    for (QString & dep : depList)
    {
        if (dep.contains("[UNKNOWN] "))
        {
            dep.remove(0, QString("[UNKNOWN] ").size());

            for (const QString & libraryDep : allLibrariesParsed)
            {
                if (libraryDep.contains(dep))
                {
                    qDebug() << "Found unknown lib:" << libraryDep;
                    dep = libraryDep;
                }
            }
        }

        dep.remove(0, currentBasePath.size());

        dep = "include(" + pwdPath + dep + ")";

        qDebug() << "Added dep:" << dep;

        depsStream << dep << endl;
    }
    deps.close();
}
