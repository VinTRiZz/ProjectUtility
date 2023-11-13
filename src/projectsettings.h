#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <atomic>
#include <mutex>
#include <QString>

#include <QDebug>

namespace Configuration
{

class IntSetting
{
public:
    IntSetting(int val) { data.store(val); }

    IntSetting(IntSetting && s) { data = s; }

    IntSetting & operator =(int newValue)
    {
        data.store(newValue);
        return *this;
    }

    operator int() { return data.load(); }

protected:
    std::atomic<int> data;
};

class StringSetting
{
public:
    StringSetting(const QString & data)
    {
        this->data = data;
    }

    StringSetting(StringSetting && s)
    {
        mx.lock();
        qDebug() << "[\033[33mCONFIG TEST\033[0m] [STRING] Copy construct:" << s;
        data = s;
        mx.unlock();
    }

    StringSetting & operator =(const QString & data)
    {
        mx.lock();
        qDebug() << "[\033[33mCONFIG TEST\033[0m] [STRING] Setting data:" << data;
        this->data = data;
        mx.unlock();
        return *this;
    }

    operator QString()
    {
        QString result;
        mx.lock();
        qDebug() << "[\033[33mCONFIG TEST\033[0m] [STRING] Getting data:" << data;
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

private:
    QString data;
    std::mutex mx;
};

struct ProjectConfiguration
{
    // Main configurations
    const QString SAVE_CHANGES_BACKUP_DIRECTORY {"./saveChangesBackup"};
    const QString BUILD_LOG_FILE_NAME {"buildLog.txt"};

    // Util class
    IntSetting PROCESS_START_TIMEOUT {5000};

    // Archivator
    IntSetting PROCESS_THREAD_TIMEOUT {60000}; // Timeout of thread in poll() function
    IntSetting ZIP_PROCESS_TIMEOUT {3600000}; // Timeout for archiving (1h)

    // Builder
    StringSetting makeProgram {"/usr/bin/make"};
    StringSetting qmakeProgram{"/usr/bin/qmake"};

    const QString qmakeDefaultBuildArgs = "PROJECT_NAME.pro -spec linux-g++";
    StringSetting qmakeArgString {""}; // Adds in settings tile
    StringSetting qmakeDebugTargetArg {"CONFIG+=debug CONFIG+=qml_debug"};
    StringSetting qmakeReleaseTargetArg {"CONFIG+=qtquickcompiler"};

    IntSetting BUILD_TIMEOUT {360000000};

    // Cleaner
    IntSetting FIND_FINISH_TIMEOUT {100000};

    StringSetting buildDirectory {"/BUILD"};
    StringSetting binDirectory {"/BIN"};
    StringSetting libDirectory {"/LIB"};
    StringSetting libraryDirectory {"/Libraries"};
    StringSetting appDirectory {"/Apps"};

    // Depends parser
    StringSetting dependPathRegexp {"\\$\\$PWD\\/\\.\\.\\/\\.\\."};
    StringSetting dependPathBase {"$$PWD/../.."};
};


static ProjectConfiguration mainProjectConfiguration {ProjectConfiguration()};

}

#endif // PROJECTSETTINGS_H
