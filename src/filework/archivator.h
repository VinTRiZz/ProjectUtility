#ifndef ARCHIVATOR_H
#define ARCHIVATOR_H

#include <memory>
#include <QString>
#include <QObject>

#include "projectsettings.h"

namespace FileWork
{

class Archivator : public QObject
{
    Q_OBJECT
public:
    Archivator(Configuration::ProjectConfiguration & mainProjectConfiguration, QObject * parent = nullptr);
    ~Archivator();

    bool addFile(const QString & path);
    bool addProject(const QString & projectDirPath);
    void clear();

    void archive(const QString & projectDirPath, const QString & resultPath);
    void archive(const QString & resultPath);

    void poll();

    bool archived() const;

signals:
    void archiveComplete();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;

    Configuration::ProjectConfiguration & mainProjectConfiguration;
};

}

#endif // ARCHIVATOR_H
