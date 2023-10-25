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
    int searchForFiles(const QString path);
    QString currentBasePath() const;

    QStringList getLibraryNameList();
    QStringList getAppNameList();

    void addLibrary(const QString & appName, const QString & libraryName);
    void removeLibrary(const QString & appName, const QString & libraryName);

    QStringList getDepends(const QString & appName);

    void poll();

    bool backupAll();
    bool loadBackup();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // PROJECTDIRECTORYFILEINTERFACE_H
