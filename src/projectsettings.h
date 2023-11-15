#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include "extendedtypes.h"

#include <QDir>

namespace Configuration
{

struct ProjectConfiguration
{
    std::map<QString, StringSetting> strSettings
    {
        // Main configurations
        { "Backup directory for changes", "./saveChangesBackup"},
        { "Log file name", "DepSearcher.log"},
        { "Configuration file path", "DepsSearcherConfig.ini" },
        { "Default base path", "/home/lazarev_as/workspace/project"},

        // Builder
        { "Make bin path", "/usr/bin/make"},
        { "Make args", "-j8"},
        { "QMake bin path", "/usr/bin/qmake"},

        { "QMake Default args", "-spec linux-g++"}, // \-spec linux\-g\+\+
        { "QMake args", ""}, // Adds in settings tile
        { "QMake Debug args", "CONFIG+=debug CONFIG+=qml_debug"},
        { "QMake Release args", "CONFIG+=qtquickcompiler"},

        { "Build directory path", "/BUILD"},
        { "Bin directory path", "/BIN"},
        { "Lib directory path", "/LIB"},
        { "Library directory path", "/Libraries"},
        { "App directory path", "/Apps"},
        { "Program default directory", QDir::currentPath().toUtf8().data() }
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
        { "Find files timeout", 100000}
    };
};


static ProjectConfiguration defaultProjectConfiguration {ProjectConfiguration()};

}

#endif // PROJECTSETTINGS_H
