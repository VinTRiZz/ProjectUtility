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

UtilFunctionClass &UtilFunctionClass::getInstance(QVector<Project> * initApps, QVector<Project> * initLibs)
{
    static UtilFunctionClass instance(initApps, initLibs);
    return instance;
}
