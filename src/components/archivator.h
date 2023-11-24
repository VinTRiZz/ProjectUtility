#ifndef ARCHIVATOR_H
#define ARCHIVATOR_H

#include <memory>
#include <QString>
#include <QObject>

#include "utilfunctionclass.h"
#include "projectsettings.h"

namespace ProjectUtility
{

class Archivator : public QObject
{
    Q_OBJECT
public:
    Archivator(UtilFunctionClass & utilClass, QObject * parent = nullptr);
    ~Archivator();

    bool addFile(const QString & path);
    bool addProject(const QString & projectDirPath);
    void clear();

    void archive(const QString & projectDirPath, const QString & resultPath);
    void archive(const QString & resultPath);

    void poll();

signals:
    void archiveComplete(bool result);

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};

}

#endif // ARCHIVATOR_H
