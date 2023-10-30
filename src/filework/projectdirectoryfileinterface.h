#ifndef PROJECTDIRECTORYFILEINTERFACE_H
#define PROJECTDIRECTORYFILEINTERFACE_H

#include <memory>
#include <QString>
#include <QObject>

namespace FileWork
{

class ProjectDirectoryFileInterface : public QObject
{
    Q_OBJECT
public:
    ProjectDirectoryFileInterface(QObject * parent = nullptr);
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

    bool build(const QString & projectName, const QString & target);
    bool rebuild(const QString & projectName, const QString & target);

    void archiveProject(const QString & projectName, const QString & resultPath);
    void archiveSelectedProject(const QStringList & projectNames, const QString & resultPath);
    void archiveAllProjects(const QString & resultPath);

    bool archiveSucceed() const;

signals:
    void archiveComplete();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // PROJECTDIRECTORYFILEINTERFACE_H
