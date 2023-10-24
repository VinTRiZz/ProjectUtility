#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <QString>
#include <QStringList>

class QFile;
namespace FileWork
{

class BackupManager
{
public:
    BackupManager();
    ~BackupManager();

    bool backup(const QString & projectName, const QString & filePath);
    bool load(const QString & projectName, const QString & filePath);
    QStringList getFileList() const;

private:
    QStringList savedFilesList;
    QFile * filesList {nullptr};

    void parseFilesList();
};

}

#endif // BACKUPMANAGER_H
