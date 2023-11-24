#include "backupmanager.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>

#include <QDebug>

using namespace ProjectUtility;

BackupManager::BackupManager(UtilFunctionClass & utilClass) :
    m_utilClass{utilClass}
{

}

BackupManager::~BackupManager()
{
    if (filesList)
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
}

bool BackupManager::backup(const QString & projectName, const QString &filePath)
{
    m_utilClass.logChannel() << "[BACKUP] Creating backup for project" << projectName << "file" << QFileInfo(filePath).baseName();

    const QString mkdirProjectCommand = QString("mkdir %1/%2 &> /dev/null").arg(backupDirectoryPath, projectName);

    system(mkdirProjectCommand.toUtf8().data());

    if (filePath.size() < 1)
        return false;

    savedFilesList << filePath;

    const QString backupFilePath = QString(backupDirectoryPath + "/%1/%2").arg( projectName, QFileInfo(filePath).baseName() );

    bool result = QFile::remove(backupFilePath);
    result = QFile::copy(filePath, backupFilePath);

    if (!result)
        m_utilClass.logChannel() << "[BACKUP] Error creating backup";
    return result;
}

bool BackupManager::load(const QString & projectName, const QString &filePath)
{
    m_utilClass.logChannel() << "[BACKUP] Loading backup of project" << projectName << "file" << QFileInfo(filePath).baseName();

    if (filePath.size() < 1)
        return false;

    const QString backupFilePath = QString(backupDirectoryPath + "/%1/%2").arg( projectName, QFileInfo(filePath).baseName() );

    bool result = QFile::remove(filePath);
    result = QFile::copy(backupFilePath, filePath);

    if (!result)
        m_utilClass.logChannel() << "[BACKUP] Error loading backup for file:" << QString(backupDirectoryPath + "/%1/%2").arg( projectName, QFileInfo(filePath).baseName() ) << "to path:" << filePath;
    return result;
}

QStringList BackupManager::getFileList() const
{
    return savedFilesList;
}

bool BackupManager::loadAll()
{
    bool result = true;
    QDir projectDir;
    QFileInfo projectFileInfo;
    for (QString & file : savedFilesList)
    {
        projectFileInfo.setFile(file);

        projectDir.setPath(projectFileInfo.absolutePath());
        if (projectDir.dirName() == "src")
            projectDir.cd("..");

        if (!load(projectDir.dirName(), file))
            result = false;
    }
    return result;
}

bool BackupManager::cd(const QString &path)
{
    m_utilClass.logChannel() << "[BACKUP] Changed backup directory from" << backupDirectoryPath << "to" << path;

    return processBackupDirectory(path);
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
    delete filesList;
    filesList = nullptr;
}

bool BackupManager::processBackupDirectory(const QString & path)
{
    if (!QFileInfo(path).exists())
    {
        backupDirectoryPath = path;
        mkdirCommand = QString("mkdir %1 &> /dev/null").arg(backupDirectoryPath);
        m_utilClass.logChannel() << "[BACKUP] Create backup directory result:" << system(mkdirCommand.toUtf8().data()); // Create backup dir
    } else if (!QFileInfo(path).isDir())
    {
        m_utilClass.logChannel() << "[BACKUP] Not a directory:" << path;
        return false;
    } else
    {
        backupDirectoryPath = path;
    }

    if (filesList)
    {
        filesList->close();
        delete filesList;
        filesList = nullptr;
    }
    filesList = new QFile(backupDirectoryPath + "/filesList.txt");
    filesList->open(QIODevice::ReadWrite);

    if (!filesList->isOpen())
    {
        system(mkdirCommand.toUtf8().data()); // Retry creating directory
        filesList->open(QIODevice::NewOnly); // Try to create file

        if (!filesList->isOpen())
        {
            throw std::runtime_error((std::string("[BACKUP] Ошибка открытия и создания файла со списком сохранённых файлов: ") + filesList->errorString().toStdString()).c_str());
        }
    }

    parseFilesList();
    return true;
}
