#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include "extendedtypes.h"

#include <QCoreApplication>

namespace Configuration
{

struct ProjectConfiguration
{
    std::map<QString, StringSetting> strSettings
    {
        // Main configurations
        { "Backup directory for changes", (QCoreApplication::applicationDirPath() + "/saveChangesBackup").toUtf8().data() },
        { "Log file name", (QCoreApplication::applicationDirPath() + "/ProjectUtility.log").toUtf8().data() },
        { "Configuration file path", (QCoreApplication::applicationDirPath() + "/ProjectUtilityConfig.ini").toUtf8().data() },
        { "Default base path", QCoreApplication::applicationDirPath().toUtf8().data()},
        { "Program default directory", QCoreApplication::applicationDirPath().toUtf8().data() },
        { "Default main template path", "$$PWD/../../template.pri"},
        { "Automatic project list update", "true" },

        // Builder
        { "Make bin path", "/usr/bin/make"},
        { "QMake bin path", "/usr/bin/qmake"},

        // Arguments
        { "Make args", "-j8"},
        { "QMake Default args", "-spec linux-g++"}, // \-spec linux\-g\+\+
        { "QMake args", ""}, // Adds in settings tile
        { "QMake Debug args", "CONFIG+=debug CONFIG+=qml_debug"},
        { "QMake Release args", "CONFIG+=qtquickcompiler"},

        // Directories
        { "Build directory path", "/BUILD"},
        { "Bin directory path", "/BIN"},
        { "Lib directory path", "/LIB"},
        { "Library directory path", "/Libraries"},
        { "App directory path", "/Apps"}
    };

    std::map<QString, IntSetting> intSettings =
    {
        // Util class
        { "Start process timeout", 5000},

        // Archivator
        { "Archive thread timeout", 60000}, // Timeout of thread in poll() function
        { "ZIP program timeout", 3600000}, // Timeout for archiving (1h)

        { "Build timeout", 360000000},

        // Cleaner
        { "Find files timeout", 100000},

        {"Maximum log size in symbols", 10000}
    };
};


static ProjectConfiguration defaultProjectConfiguration {ProjectConfiguration()};

}

#endif // PROJECTSETTINGS_H
