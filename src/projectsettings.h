#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include "extendedtypes.h"

#include <QApplication>

namespace Configuration
{

struct ProjectConfiguration
{
    ProjectConfiguration() = default;
    ProjectConfiguration(const QString & basePath)
    {
        // Main configurations
        strSettings["Backup directory for changes"] = (basePath + "/saveChangesBackup").toUtf8().data();
        strSettings["Log file name"] = (basePath + "/ProjectUtility.log").toUtf8().data();
        strSettings["Configuration file path"] = (basePath + "/ProjectUtilityConfig.ini").toUtf8().data();
        strSettings["Default base path"] = basePath.toUtf8().data();
        strSettings["Program default directory"] = basePath.toUtf8().data();
    }
    ~ProjectConfiguration() = default;

    ProjectConfiguration & operator =(const ProjectConfiguration & other)
    {
        strSettings = other.strSettings;
        intSettings = other.intSettings;
        return *this;
    }

    std::map<QString, StringSetting> strSettings
    {
        // Main configurations
        { "Backup directory for changes", "./saveChangesBackup" },
        { "Log file name", "./ProjectUtility.log" },
        { "Configuration file path", "./ProjectUtilityConfig.ini" },
        { "Default base path", "" },
        { "Program default directory", "" },
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

        // Etc
        { "Cppcheck arguments", "--verbose --enable=all" }, // cppcheck
        { "Cppcheck arguments", "--verbose --enable=all" } // cppcheck
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
