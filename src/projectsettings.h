#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <atomic>
#include <QString>

namespace Configuration
{

class IntSetting
{
public:
    IntSetting(int val) { data.store(val); }

    IntSetting & operator =(int newValue)
    {
        data.store(newValue);
        return *this;
    }

    operator int() { return data.load(); }

protected:
    std::atomic<int> data;
};

struct ProjectConfiguration
{
    // Util class config
    IntSetting PROCESS_START_TIMEOUT {5000};

    // Archivator config
    IntSetting PROCESS_THREAD_TIMEOUT {60000}; // Timeout of thread in poll() function
    IntSetting ZIP_PROCESS_TIMEOUT {3600000}; // Timeout for archiving (1h)

    // Builder
    QString makeProgram {"/usr/bin/make"};
    QString qmakeProgram{"/usr/bin/qmake"};

    const QString qmakeDefaultBuildArgs = "PROJECT_NAME.pro -spec linux-g++";
    QString qmakeArgString {""}; // Adds in settings tile
    QString qmakeDebugTargetArg {"CONFIG+=debug CONFIG+=qml_debug"};
    QString qmakeReleaseTargetArg {"CONFIG+=qtquickcompiler"};
};


static ProjectConfiguration mainProjectConfiguration;

}

#endif // PROJECTSETTINGS_H
