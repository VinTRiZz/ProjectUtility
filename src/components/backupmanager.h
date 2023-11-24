#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <QString>
#include <QStringList>

#include "utilfunctionclass.h"

class QFile;
namespace ProjectUtility
{

class BackupManager
{
public:
    BackupManager(UtilFunctionClass & utilClass);
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

    UtilFunctionClass & m_utilClass;
};

}

#endif // BACKUPMANAGER_H
