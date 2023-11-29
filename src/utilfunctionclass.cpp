#include "utilfunctionclass.h"

#include "projectsettings.h"

#include <QProcess>
#include <QDebug>

using namespace ProjectUtility;

UtilFunctionClass::UtilFunctionClass(QVector<Project> * initApps, QVector<Project> * initLibs, std::shared_ptr<Configuration::ProjectConfiguration> mainProjectConfiguration, QObject * parent) :
    QObject(parent),
    apps(initApps),
    libs(initLibs),
    mainProjectConfiguration(mainProjectConfiguration)
{

}

UtilFunctionClass::~UtilFunctionClass()
{
    printBuffer();
}

void UtilFunctionClass::printBuffer()
{
    if (!outputBuffer.size())
        return;

    QString output;
    for (QVariant part : outputBuffer)
    {
        output += part.toString() + " ";
    }
    outputBuffer.clear();
    qDebug() << output.toUtf8().data();
    writeLog(output);
}

UtilFunctionClass::UtilFunctionClass(QObject * parent) :
    QObject(parent)
{

}

void UtilFunctionClass::logParsedProjects()
{
    int currentIteration = 1;
    logChannel() << "--------------------------------------------------------------------------------------------------------";
    logChannel() << "\033[32mFound apps:\033[0m";
    for (Project & app : *apps)
    {
        logChannel() << "\033[33mAPP N:" << currentIteration++ << "\033[0m"   << "\n"
                 << "NAME:  " << app.name                                 << "\n"
                 << "PRO:   " << app.projectProFilePath                   << "\n"
                 << "DEPS:  " << app.dependFilePath                       << "\n"
                 << "DEPON: " << app.depends.join(", ")                   << "\n"
                    ;
    }

    logChannel() << "--------------------------------------------------------------------------------------------------------";

    currentIteration = 1;
    logChannel() << "\033[32mFound libraries:\033[0m";
    for (Project & lib : *libs)
    {
        logChannel() << "\033[33mLIBRARY N:" << currentIteration++ << "\033[0m" << "\n"
                 << "NAME: " << lib.name                                    << "\n"
                 << "PRO:  " << lib.projectProFilePath                      << "\n"
                 << "DEPS: " << lib.dependFilePath                          << "\n"
                 << "USE:  " << lib.useFilePath
                 << "DEPON: " << lib.depends.join(", ")                   << "\n"
                    ;
    }
    logChannel() << "--------------------------------------------------------------------------------------------------------";
}

bool UtilFunctionClass::invoke(const QString &program, const QStringList & args, const int timeout)
{
    QProcess invokingProcess;

    invokingProcess.setProgram(program);
    invokingProcess.setArguments(args);

    invokingProcess.start();
    if (!invokingProcess.waitForStarted(mainProjectConfiguration->intSettings["Start process timeout"]))
    {
        logChannel() << "[UTIL CLASS] Invoke start timeout, program: [" << program << "] args: [" << args.join(" ") << "]";
        writeLog(QString("Invoke timeout"));
        return false;
    }

    if (!invokingProcess.waitForFinished(timeout))
    {
        logChannel() << "[UTIL CLASS] Invoke finish timeout, program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    if (invokingProcess.exitCode())
    {
        logChannel() << "[UTIL CLASS] Invoke error (exit code" << invokingProcess.exitCode() << "), program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    return true;
}

bool UtilFunctionClass::invoke(const QString &program, const QStringList & args, QString &outputBuffer, const int timeout)
{
    QProcess invokingProcess;

    invokingProcess.setProgram(program);
    invokingProcess.setArguments(args);

    invokingProcess.start();
    if (!invokingProcess.waitForStarted(mainProjectConfiguration->intSettings["Start process timeout"]))
    {
        logChannel() << "[UTIL CLASS] Invoke start timeout, program: [" << program << "] args: [" << args.join(" ") << "]";
        writeLog(QString("Invoke timeout"));
        return false;
    }

    if (!invokingProcess.waitForFinished(timeout))
    {
        logChannel() << "[UTIL CLASS] Invoke finish timeout, program: [" << program << "] args: [" << args.join(" ") << "]";

        writeLog(invokingProcess.readAllStandardError());
        writeLog(invokingProcess.readAllStandardOutput());
        return false;
    }

    if (invokingProcess.exitCode())
    {
        logChannel() << "[UTIL CLASS] Invoke error (exit code" << invokingProcess.exitCode() << "), program: [" << program << "] args: [" << args.join(" ") << "]";

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

void UtilFunctionClass::writeLog(const QVariant & what)
{
    if (m_logFile.fileName() < 2)
        return;

    const QString logFileName = mainProjectConfiguration->strSettings["Log file name"];

    if (logFileName != m_logFile.fileName())
    {
        setLogFile(logFileName);
    }

    m_logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    if (m_logFile.isOpen())
    {
        QTextStream logStream(&m_logFile);

        logStream << what.toString() << endl;
    }
    m_logFile.close();

    emit log(what);
}

UtilFunctionClass &UtilFunctionClass::logChannel()
{
    outputStarted = true;
    return *this;
}

UtilFunctionClass &UtilFunctionClass::operator <<(const QVariant &data)
{
    if (outputStarted)
    {
        printBuffer();
        outputStarted = false;
    }
    outputBuffer.push_back(data);
    return *this;
}

bool UtilFunctionClass::hasRecurseDepend(QStringList &dependQuery, Project *pParent)
{
    Project * depProj {nullptr};
    int dependQuerySize = dependQuery.size();
    bool recurseExist;
    for (QString & depName : pParent->depends)
    {
        recurseExist = dependQuery.contains(depName);
        dependQuery << depName;

        if (recurseExist)
            return true;

        // Find library by name
        depProj = getProject(depName);

        if (depProj)
        {
            if (hasRecurseDepend(dependQuery, depProj))
                return true;
        }
        dependQuery.erase(dependQuery.begin() + dependQuerySize, dependQuery.end());
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

bool UtilFunctionClass::hasDepend(const Project *proj, const QString & libName)
{
    Project * pProj;
    bool hasDependInRecurse {false};

    if (proj->name == libName)
        return true;

    for (const QString & depName : proj->depends)
    {
        pProj = getProject(depName);

        if (pProj)
        {
            if (pProj->name == libName)
                return true;

            hasDependInRecurse = hasDepend(pProj, libName);

            if (hasDependInRecurse)
                return true;
        }
    }
    return false;
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

void UtilFunctionClass::increasePercent(const float value)
{
    processPercent.store(processPercent.load() + value);
}

void UtilFunctionClass::setPercent(const float newVal)
{
    processPercent.store(newVal);
}

float UtilFunctionClass::currentPercent() const
{
    return processPercent.load();
}

Configuration::ProjectConfiguration & UtilFunctionClass::projectConfiguration()
{
    if (!mainProjectConfiguration)
    {
        throw std::runtime_error("Invalid initialization querry");
    }
    return *mainProjectConfiguration;
}

UtilFunctionClass &UtilFunctionClass::getInstance(QVector<Project> * initApps, QVector<Project> * initLibs, std::shared_ptr<Configuration::ProjectConfiguration> mainProjectConfiguration)
{
    static UtilFunctionClass instance(initApps, initLibs, mainProjectConfiguration);
    return instance;
}
