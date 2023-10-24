#include "backupmanager.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include <QDebug>

#define BACKUP_DIRECTORY "./backups"

using namespace FileWork;

BackupManager::BackupManager()
{
    qDebug() << "[BACKUP] Create backup directory result:" << system("mkdir " BACKUP_DIRECTORY " &> /dev/null"); // Create backup dir

    filesList = new QFile(BACKUP_DIRECTORY "/filesList.txt");
    filesList->open(QIODevice::ReadWrite);

    if (!filesList->isOpen())
    {
        system("mkdir " BACKUP_DIRECTORY " &> /dev/null"); // Retry creating directory
        filesList->open(QIODevice::NewOnly); // Try to create file

        if (!filesList->isOpen())
        {
            throw std::runtime_error((std::string("Ошибка открытия и создания файла со списком сохранённых файлов: ") + filesList->errorString().toStdString()).c_str());
        }
    }

    parseFilesList();
}

BackupManager::~BackupManager()
{
    filesList->open(QIODevice::Truncate | QIODevice::WriteOnly);

    if (!filesList->isOpen())
    {
        delete filesList;
        return;
    }

    QTextStream fileStream(filesList);
    for (QString & path : savedFilesList)
    {
        fileStream << path << endl;
    }

    delete filesList;
}

bool BackupManager::backup(const QString & projectName, const QString &filePath)
{
    qDebug() << "[BACKUP] Creating backup for project" << projectName << "file" << QFileInfo(filePath).baseName();

    const QString mkdirCommand = "mkdir " BACKUP_DIRECTORY "/" + projectName + " &> /dev/null";

    system(mkdirCommand.toUtf8().data());

    if (filePath.size() < 1)
        return false;

    savedFilesList << filePath;

    bool result = QFile::copy(filePath, QString(BACKUP_DIRECTORY "/%1/%2").arg( projectName, QFileInfo(filePath).baseName() ));
    if (!result)
        qDebug() << "[BACKUP] Error creating backup";
    return result;
}

bool BackupManager::load(const QString & projectName, const QString &filePath)
{
    qDebug() << "[BACKUP] Loading backup of project" << projectName << "file" << QFileInfo(filePath).baseName();

    if (filePath.size() < 1)
        return false;

    bool result = QFile::copy(QString(BACKUP_DIRECTORY "/%1/%2").arg( projectName, QFileInfo(filePath).baseName() ), filePath);
    if (!result)
        qDebug() << "[BACKUP] Error loading backup";
    return result;
}

QStringList BackupManager::getFileList() const
{
    return savedFilesList;
}

void BackupManager::parseFilesList()
{
    QString fileListData = filesList->readAll();
    QString buffer;

    int copyFrom = 0,
        copyTo = 0;
    for (; copyTo < fileListData.size(); copyTo++)
    {
        copyTo = fileListData.indexOf(QChar(0x0A), copyFrom);
        if (copyTo != copyFrom)
        {
            buffer.clear();
            buffer.resize(copyTo - copyFrom);
            std::copy(fileListData.data() + copyFrom, fileListData.data() + copyTo, buffer.begin());
            copyFrom = copyTo + 1;

            savedFilesList << buffer;
        }
    }

    filesList->close();
}
