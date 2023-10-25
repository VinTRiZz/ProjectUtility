#include "dependencyparser.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <QDebug>

using namespace FileWork;

DependencyParser::DependencyParser(QVector<Project> & apps, QVector<Project> & libs):
    apps{apps}, libs{libs}
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
    qDebug() << "[PARSING DEPENDS]";

    if (currentBasePath.size() > 0)
    {
        for (Project & app : apps)
            parseDepends(app);

        for (Project & lib : libs)
            parseDepends(lib);
    }

    qDebug() << "[PARSED]";
}

void DependencyParser::parseDepends(Project &proj)
{
    if (proj.dependFilePath.isEmpty())
        return;

    QFile deps(proj.dependFilePath);

    deps.open(QIODevice::ReadOnly);

    if (!deps.isOpen())
    {
        qDebug() << "File not opened with error:" << deps.errorString() << ", path:" << deps.fileName();
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

    while (includeStartPos != depsFileContents.end())
    {
        includeStartPos = std::search(includeStartPos, depsFileContents.end(), INCLUDE_STRING.begin(), INCLUDE_STRING.end());

        if (includeStartPos == depsFileContents.end())
            break;

        beginBracketPos = std::find(includeStartPos, depsFileContents.end(), '(');
        endBracketPos = std::find(beginBracketPos, depsFileContents.end(), ')');

        if (beginBracketPos != endBracketPos)
        {
            buffer = std::string(beginBracketPos + 1, endBracketPos).c_str();
            buffer.replace(QRegExp("\\$\\$PWD\\/\\.\\.\\/\\.\\."), currentBasePath);
            depPaths << buffer;
        }
        includeStartPos++;
    }

    QStringList parsedDeps;
    QStringList::iterator existDepPos;
    for (QString & dep : depPaths)
    {
        existDepPos = std::find_if(
            proj.depends.begin(), proj.depends.end(),
            [&dep](QString & depName)
            {
                return dep.contains(depName);
            }
        );

        if (existDepPos == proj.depends.end())
            parsedDeps << dep;
    }

    for (QString & dep : parsedDeps)
    {
        dep.chop(QFileInfo(dep).fileName().size());
        proj.depends << QDir(dep).dirName();
        qDebug() << "Parsed dep:" << proj.name << "--->" << proj.depends.last();
    }
}
