#include "utilfunctionclass.h"

#include <QProcess>
#include <QDebug>

#define PROCESS_START_TIMEOUT 5000

using namespace FileWork;

UtilFunctionClass::UtilFunctionClass(QVector<Project> * initApps, QVector<Project> * initLibs) :
    apps(initApps),
    libs(initLibs)
{

}

UtilFunctionClass::~UtilFunctionClass()
{

}

UtilFunctionClass::UtilFunctionClass()
{

}

void UtilFunctionClass::logParsedProjects()
{
    int currentIteration = 1;
    qDebug() << "--------------------------------------------------------------------------------------------------------";
    qDebug() << "\033[32mFound apps:\033[0m";
    for (Project & app : *apps)
    {
        qDebug() << "\033[33mAPP N:" << currentIteration++ << "\033[0m"   << endl
                 << "NAME:  " << app.name                                 << endl
                 << "PRO:   " << app.projectProFilePath                   << endl
                 << "DEPS:  " << app.dependFilePath                       << endl
                 << "DEPON: " << app.depends.join(", ")                   << endl
                    ;
    }

    qDebug() << "--------------------------------------------------------------------------------------------------------";

    currentIteration = 1;
    qDebug() << "\033[32mFound libraries:\033[0m";
    for (Project & lib : *libs)
    {
        qDebug() << "\033[33mLIBRARY N:" << currentIteration++ << "\033[0m" << endl
                 << "NAME: " << lib.name                                    << endl
                 << "PRO:  " << lib.projectProFilePath                      << endl
                 << "DEPS: " << lib.dependFilePath                          << endl
                 << "USE:  " << lib.useFilePath
                    ;
    }
    qDebug() << "--------------------------------------------------------------------------------------------------------";
}

bool UtilFunctionClass::invoke(const QString &program, const QStringList args, const int timeout)
{
    QProcess invokingProcess;

    invokingProcess.setProgram(program);
    invokingProcess.setArguments(args);

    invokingProcess.start();
    if (!invokingProcess.waitForStarted(PROCESS_START_TIMEOUT))
    {
        qDebug() << "[UTIL CLASS] Invoke start timeout, program: [" << program << "] args: [" << args.join(" ") << "]";
        writeLog("Invoke timeout");
        return false;
    }

    if (!invokingProcess.waitForFinished(timeout))
    {
        qDebug() << "[UTIL CLASS] Invoke finish timeout, program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    if (invokingProcess.exitCode())
    {
        qDebug() << "[UTIL CLASS] Invoke error (exit code" << invokingProcess.exitCode() << "), program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    return true;
}

bool UtilFunctionClass::invoke(const QString &program, const QStringList args, QString &outputBuffer, const int timeout)
{
    QProcess invokingProcess;

    invokingProcess.setProgram(program);
    invokingProcess.setArguments(args);

    invokingProcess.start();
    if (!invokingProcess.waitForStarted(PROCESS_START_TIMEOUT))
    {
        qDebug() << "[UTIL CLASS] Invoke start timeout, program: [" << program << "] args: [" << args.join(" ") << "]";
        writeLog("Invoke timeout");
        return false;
    }

    if (!invokingProcess.waitForFinished(timeout))
    {
        qDebug() << "[UTIL CLASS] Invoke finish timeout, program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    if (invokingProcess.exitCode())
    {
        qDebug() << "[UTIL CLASS] Invoke error (exit code" << invokingProcess.exitCode() << "), program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    outputBuffer = invokingProcess.readAllStandardOutput();
    return true;
}

void UtilFunctionClass::setLogFile(const QString &logPath)
{
    if (logPath.size() > 1)
    {
        m_logFile.setFileName(logPath);
        m_logFile.open(QIODevice::Truncate | QIODevice::WriteOnly);
        m_logFile.close();
    }
}

void UtilFunctionClass::writeLog(const QByteArray &what)
{
    if ((m_logFile.fileName() < 2) || (!what.size()))
        return;

    m_logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    if (m_logFile.isOpen())
    {
        m_logFile.write(QByteArray("\n---------------------------------------------------------------------------\n"));
        m_logFile.write( what );
        m_logFile.write(QByteArray("\n---------------------------------------------------------------------------\n"));
    }
    m_logFile.close();
}

bool UtilFunctionClass::hasRecurseDepend(QStringList &dependQuery, Project *pParent)
{
    Project * depProj {nullptr};
    for (QString & depName : pParent->depends)
    {
        if (dependQuery.contains(depName))
        {
            dependQuery << depName;
            return true;
        }
        dependQuery << depName;

        for (Project & lib : *libs)
        {
            if (lib.name == depName)
            {
                depProj = &lib;
                break;
            }
        }

        if (depProj)
        {
            if (hasRecurseDepend(dependQuery, depProj))
                return true;
        }
    }
    return false;
}

Project *UtilFunctionClass::getProject(const QString &projectName)
{
    auto projectPos = std::find_if(apps->begin(), apps->end(), [&projectName](Project & app){ return (app.name == projectName); });

    if (projectPos == apps->end())
    {
        projectPos = std::find_if(libs->begin(), libs->end(), [&projectName](Project & app){ return (app.name == projectName); });

        if (projectPos == libs->end())
            return nullptr;
    }

    return projectPos;
}

QStringList UtilFunctionClass::getLibraryNameList()
{
    QStringList result;
    for (const Project & lib : *libs)
    {
        result << lib.name;
    }
    return result;
}

QStringList UtilFunctionClass::getAppNameList()
{
    QStringList result;
    for (const Project & app : *apps)
    {
        result << app.name;
    }
    return result;
}

UtilFunctionClass &UtilFunctionClass::getInstance(QVector<Project> * initApps, QVector<Project> * initLibs)
{
    static UtilFunctionClass instance(initApps, initLibs);
    return instance;
}
