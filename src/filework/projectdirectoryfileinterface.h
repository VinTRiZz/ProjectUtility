#ifndef PROJECTDIRECTORYFILEINTERFACE_H
#define PROJECTDIRECTORYFILEINTERFACE_H

#include <memory>
#include <QString>

namespace FileWork
{

class ProjectDirectoryFileInterface
{
public:
    ProjectDirectoryFileInterface();
    ~ProjectDirectoryFileInterface();

    // Returns count of files found
    int processDirectory(const QString path);
    QString currentDirectory() const;

    QStringList getLibraryNameList();
    QStringList getAppNameList();

    void addLibrary(const QString & projectName, const QString & libraryName);
    void removeLibrary(const QString & projectName, const QString & libraryName);

    void saveChanges();

    int progressPercent() const;

    QStringList getDepends(const QString & appName);

    void poll();

    bool backupAll(const QString & backupDirectory);
    bool loadBackup(const QString & backupDirectory);

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // PROJECTDIRECTORYFILEINTERFACE_H
