#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <atomic>
#include <mutex>
#include <QString>
#include <map>

#include <QDebug>

namespace Configuration
{

class IntSetting
{
public:
    IntSetting()        { data.store(0); }
    IntSetting(int val) { data.store(val); }

    IntSetting(const IntSetting & s) { data.store(s.data.load()); }
    IntSetting(IntSetting && s) { data.store(s.data.load()); }

    IntSetting & operator =(int newValue)
    {
        data.store(newValue);
        return *this;
    }

    IntSetting & operator =(const IntSetting newValue)
    {
        data.store(newValue.data.load());
        return *this;
    }

    operator int() const { return data.load(); }

protected:
    std::atomic<int> data;
};

class StringSetting
{
public:
    StringSetting()
    {
        this->data = QString();
    }

    StringSetting(const char * data)
    {
        this->data = data;
    }

    StringSetting(const StringSetting & data)
    {
        this->data = data.data;
    }

    StringSetting(StringSetting && s)
    {
        mx.lock();
        data = s;
        mx.unlock();
    }

    StringSetting & operator =(const QString & data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator =(StringSetting & data)
    {
        mx.lock();
        this->data = data;
        mx.unlock();
        return *this;
    }

    StringSetting & operator =(const StringSetting & data)
    {
        mx.lock();
        this->data = data.data;
        mx.unlock();
        return *this;
    }

    operator QString()
    {
        QString result;
        mx.lock();
        result = data;
        mx.unlock();
        return data;
    }

    bool isEmpty()
    {
        bool result;
        mx.lock();
        result = data.isEmpty();
        mx.unlock();
        return result;
    }

    QByteArray toUtf8() const
    {
        QByteArray result;
        mx.lock();
        result = data.toUtf8();
        mx.unlock();
        return result;
    }

private:
    QString data;
    mutable std::mutex mx;
};

struct ProjectConfiguration
{
    std::map<QString, StringSetting> strSettings
    {
        // Main configurations
        { "SAVE_CHANGES_BACKUP_DIRECTORY", "./saveChangesBackup"},
        { "BUILD_LOG_FILE_NAME", "buildLog.txt"},
        { "Configuration file path", "DepsSearcherConfig.ini" },

        // Builder
        { "makeProgram", "/usr/bin/make"},
        { "qmakeProgram", "/usr/bin/qmake"},

        { "qmakeDefaultBuildArgs", "-spec linux-g++"},
        { "qmakeArgString", ""}, // Adds in settings tile
        { "qmakeDebugTargetArg", "CONFIG+=debug CONFIG+=qml_debug"},
        { "qmakeReleaseTargetArg", "CONFIG+=qtquickcompiler"},

        { "buildDirectory", "/BUILD"},
        { "binDirectory", "/BIN"},
        { "libDirectory", "/LIB"},
        { "libraryDirectory", "/Libraries"},
        { "appDirectory", "/Apps"},

        // Depends parser
        { "dependPathRegexp", "\\$\\$PWD\\/\\.\\.\\/\\.\\."},
        { "dependPathBase", "$$PWD/../.."}
    };

    std::map<QString, IntSetting> intSettings =
    {
        // Util class
        { "PROCESS_START_TIMEOUT", 5000},

        // Archivator
        { "PROCESS_THREAD_TIMEOUT", 60000}, // Timeout of thread in poll() function
        { "ZIP_PROCESS_TIMEOUT", 3600000}, // Timeout for archiving (1h)

        { "BUILD_TIMEOUT", 360000000},

        // Cleaner
        { "FIND_FINISH_TIMEOUT", 100000}
    };
};


static ProjectConfiguration defaultProjectConfiguration {ProjectConfiguration()};

}

#endif // PROJECTSETTINGS_H
