#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <QString>
#include <QStringList>

#include "projectsettings.h"

class QFile;
namespace DependsSearcher
{

class BackupManager
{
public:
    BackupManager(Configuration::ProjectConfiguration & mainProjectConfiguration);
    ~BackupManager();

    bool backup(const QString & projectName, const QString & filePath);
    bool load(const QString & projectName, const QString & filePath);
    QStringList getFileList() const;

    bool loadAll();

    bool cd(const QString & path);

private:
    QString backupDirectoryPath {"./backups"};
    QString mkdirCommand = QString("mkdir %1 &> /dev/null").arg(backupDirectoryPath);
    QStringList savedFilesList;
    QFile * filesList {nullptr};

    void parseFilesList();
    bool processBackupDirectory(const QString & path);

    Configuration::ProjectConfiguration & mainProjectConfiguration;
};

}

#endif // BACKUPMANAGER_H
