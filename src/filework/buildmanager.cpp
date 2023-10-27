#include "buildmanager.h"

#include <QDebug>
#include <QProcess>

#include <QDir>

#define BUILD_START_TIMEOUT 1000

using namespace FileWork;

BuildManager::BuildManager(QObject * parent) :
    QObject(parent)
{

}

BuildManager::~BuildManager()
{

}

bool BuildManager::build(const Project &proj, const QString target, const int timeout)
{
    if (m_isWorking)
        return false;
    m_isWorking = true;

    writeLog(QString("Project build \"%1\" with target \"%2\" started").arg(proj.name, target).toUtf8());

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList qmakeArgs;
    qmakeArgs << proj.name + ".pro" << "\-spec" << "linux\-g\+\+";

    if (target == "debug")
        qmakeArgs << "CONFIG+=debug CONFIG+=qml_debug";
    else if (target == "release")
        qmakeArgs << "CONFIG+=qtquickcompiler";
    else
    {
        qDebug() << "[BUILD MANAGER] No target selected";
        writeLog("No target selected");
        return false;
    }

    QStringList buildArgs;

    // Stage 1
    if (!invoke("/usr/bin/qmake", qmakeArgs, timeout))
    {
        m_isWorking = false;
        return false;
    }

    // Stage 2
    if (!invoke("/usr/bin/make", buildArgs, timeout))
    {
        m_isWorking = false;
        return false;
    }

    QDir::setCurrent(currentDir);

    m_isWorking = false;
    return true;
}

bool BuildManager::rebuild(const Project &proj, const QString target, const int timeout)
{
    if (m_isWorking)
        return false;

    m_isWorking = true;

    writeLog("Project rebuild started");

    const QString currentDir = QDir::currentPath();
    const QString projectDir = QFileInfo(proj.projectProFilePath).absolutePath();

    QDir::setCurrent(projectDir);

    QStringList cleanArgs;
    cleanArgs << "clean";

    QDir::setCurrent(projectDir);
    invoke("/usr/bin/make", cleanArgs, timeout);
    QDir::setCurrent(currentDir);

    m_isWorking = false;
    return build(proj, target, timeout);
}

void BuildManager::setLogFile(const QString &logPath)
{
    if (logPath.size() > 1)
    {
        m_logFile.setFileName(logPath);
        m_logFile.open(QIODevice::Truncate | QIODevice::WriteOnly);
        m_logFile.close();
    }
}

void BuildManager::writeLog(const QByteArray & what)
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

bool BuildManager::invoke(const QString &program, const QStringList args, const int timeout)
{
    QProcess invokingProcess;

    invokingProcess.setProgram(program);
    invokingProcess.setArguments(args);

    invokingProcess.start();
    if (!invokingProcess.waitForStarted(BUILD_START_TIMEOUT))
    {
        qDebug() << "[BUILD MANAGER] Invoke start timeout, program: [" << program << "] args: [" << args.join(" ") << "]";
        writeLog("Invoke timeout");
        m_isWorking = false;
        return false;
    }

    if (!invokingProcess.waitForFinished(timeout))
    {
        qDebug() << "[BUILD MANAGER] Invoke finish timeout, program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        m_isWorking = false;
        return false;
    }

    if (invokingProcess.exitCode())
    {
        m_isWorking = false;
        qDebug() << "[BUILD MANAGER] Invoke error (exit code" << invokingProcess.exitCode() << "), program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        m_isWorking = false;
        return false;
    }

    return true;
}
