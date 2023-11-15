#include "projectbasegenerator.h"

#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

using namespace DependsSearcher;

ProjectBaseGenerator::ProjectBaseGenerator(UtilFunctionClass & utilClass) :
    m_utilClass(utilClass)
{

}

DependsSearcher::ProjectBaseGenerator::~ProjectBaseGenerator()
{

}

bool ProjectBaseGenerator::generateProject(const ProjectBaseConfiguration &config)
{
    QString projectName = config.projectName;

    if (projectName.contains(" "))
        projectName.remove(QRegExp(" "));

    try
    {
        qDebug() << "[PROJECT GENERATOR] Started generating project" << projectName << "by path" << config.baseDir;

        const QString projectBaseDir = config.baseDir + "/" + projectName;

        QStringList commandArgs;

        // Create directories
        commandArgs << projectBaseDir;
        if (!m_utilClass.invoke("mkdir", commandArgs, m_utilClass.projectConfiguration().intSettings["Start process timeout"]))
        {
            qDebug() << "[PROJECT GENERATOR] Error creating project directory:" << commandArgs.join(""); // Command args must has 1 arg here
            throw std::runtime_error("Base dir create error");
        }

        // Create .pro file
        QFile proFile(projectBaseDir + "/" + projectName + ".pro");
        proFile.open(QIODevice::WriteOnly);

        QTextStream proFileStream(&proFile);

        if (config.hasGui)
            proFileStream << "QT += core gui" << endl << "greaterThan(QT_MAJOR_VERSION, 4): QT += widgets" << endl << endl;
        else
            proFileStream << "QT += core" << endl << "CONFIG += c++11 console" << endl << endl;

        proFileStream
                << "INCLUDEPATH += src" << endl
                << "TEMPLATE = ";

        if (config.isLibrary)
            proFileStream << "lib";
        else
            proFileStream << "app";

        proFileStream << endl;

        proFileStream << "TARGET = " << projectName << endl << endl;

        // Create library things
        if (config.isLibrary)
        {
            commandArgs.last() = projectBaseDir + "/include";
            if (!m_utilClass.invoke("mkdir", commandArgs, m_utilClass.projectConfiguration().intSettings["Start process timeout"]))
            {
                qDebug() << "[PROJECT GENERATOR] Error creating directory:" << commandArgs.join(""); // Command args must has 1 arg here
                throw std::runtime_error("Include dir create error");
            }

            commandArgs.last() = projectBaseDir + "/include/" + projectName;
            if (!m_utilClass.invoke("mkdir", commandArgs, m_utilClass.projectConfiguration().intSettings["Start process timeout"]))
            {
                qDebug() << "[PROJECT GENERATOR] Error creating directory:" << commandArgs.join(""); // Command args must has 1 arg here
                throw std::runtime_error("Include-named dir create error");
            }

            QFile useFile(projectBaseDir + "/use.pri");
            useFile.open(QIODevice::WriteOnly);

            if (!useFile.isOpen())
            {
                qDebug() << "[PROJECT GENERATOR] Error creating use.pri:" << useFile.errorString();
                throw std::runtime_error("use.pri create error");
            }

            QTextStream useFileStream(&useFile);

            useFileStream
                    << "INCLUDEPATH += $$PWD/include" << endl << endl
                    << "LIBS += -L$$PWD/BIN/ -l" << projectName;

            useFile.close();
        }


        // Create source directory
        commandArgs.last() = projectBaseDir + "/src";
        if (!m_utilClass.invoke("mkdir", commandArgs, m_utilClass.projectConfiguration().intSettings["Start process timeout"]))
        {
            qDebug() << "[PROJECT GENERATOR] Error creating directory:" << commandArgs.join(""); // Command args must has 1 arg here
            throw std::runtime_error("Source dir create error");
        }

        if (QFileInfo(":/templates").exists())
        {
            qDebug() << "\033[32mEXIST!\033[0m";
        }

        // Create basic files
        if (config.hasGui)
        {
            if (
                    !QFile::copy(":/gui/resourceFiles/templates_gui/mainwindow.h", projectBaseDir + "/src/mainwindow.h") ||
                    !QFile::copy(":/gui/resourceFiles/templates_gui/mainwindow.cpp", projectBaseDir + "/src/mainwindow.cpp") ||
                    !QFile::copy(":/gui/resourceFiles/templates_gui/mainwindow.ui", projectBaseDir + "/src/mainwindow.ui")
                )
            {
                qDebug() << "[PROJECT GENERATOR] Error creating GUI files";
                throw std::runtime_error("GUI copy error");
            }

            if (!config.isLibrary)
            {
                if (!QFile::copy(":/gui/resourceFiles/templates_gui/main.cpp", projectBaseDir + "/src/main.cpp"))
                {
                    qDebug() << "[PROJECT GENERATOR] Error creating GUI files";
                    throw std::runtime_error("GUI copy error (main)");
                }
            }
        }
        else if (!config.isLibrary)
        {
            if (!QFile::copy(":/console/resourceFiles/templates_console/main.cpp", projectBaseDir + "/src/main.cpp"))
            {
                qDebug() << "[PROJECT GENERATOR] Error creating Console files";
                throw std::runtime_error("Console copy error (main)");
            }
        }


        // Create deps file
        if (config.hasDeps)
        {
            QFile depsFile(projectBaseDir + "/deps.pri");
            depsFile.open(QIODevice::WriteOnly);
            depsFile.write("\n");
            depsFile.close();

            proFileStream << "include(deps.pri)" << endl;
        }

        QFile srcFile(projectBaseDir + "/src/src.pri");
        srcFile.open(QIODevice::WriteOnly);
        QTextStream srcFileStream(&srcFile);

        srcFileStream << "SOURCES += src/*.cpp" << endl << "HEADERS += src/*.h" << endl;

        if (config.hasGui)
            srcFileStream << "FORMS += src/*.ui" << endl;

        srcFile.close();

        proFileStream << "include(src/src.pri)" << endl;

        if (!m_utilClass.projectConfiguration().strSettings["Default main template path"].isEmpty())
            proFileStream << "include(" << m_utilClass.projectConfiguration().strSettings["Default main template path"] << ")" << endl;

        if (config.hasBuildPri)
        {
            QFile buildPriFile(projectBaseDir + "/build.pri");
            buildPriFile.open(QIODevice::WriteOnly);
            QTextStream buildPriFileStream(&buildPriFile);

            buildPriFileStream
                    << "BUILD_PATH = $$PWD/BUILD" << endl
                    << "BIN_PATH   = $$PWD/BIN" << endl << endl
                    << "DESTDIR     = $$BIN_PATH" << endl << endl
                    << "OBJECTS_DIR = $$BUILD_PATH" << endl
                    << "MOC_DIR     = $$BUILD_PATH" << endl
                    << "RCC_DIR     = $$BUILD_PATH" << endl
                    << "UI_DIR      = $$BUILD_PATH" << endl
            ;

            buildPriFile.close();

            proFileStream << "include(build.pri)";
        }

        proFile.close();

        qDebug() << "[PROJECT GENERATOR] Project generated";
        return true;
    }
    catch (std::runtime_error & ex)
    {
        // Must be thrown only my errors... Must be
        qDebug() << "[PROJECT GENERATOR] Got exception with text:" << ex.what();

        QString test("Base dir create error");
        if (test != ex.what())
        {
            QStringList commandArgs;
            commandArgs << config.baseDir + "/" + projectName << "-R";
            m_utilClass.invoke("rm", commandArgs, m_utilClass.projectConfiguration().intSettings["Start process timeout"]);
        }

        return false;
    }
}
