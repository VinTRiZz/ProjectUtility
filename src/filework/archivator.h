#ifndef ARCHIVATOR_H
#define ARCHIVATOR_H

#include <memory>
#include <QString>
#include <QObject>

namespace FileWork
{

class Archivator : public QObject
{
    Q_OBJECT
public:
    Archivator(QObject * parent = nullptr);
    ~Archivator();

    bool addFile(const QString & path);
    bool addProject(const QString & projectDirPath);

    void archive(const QString & resultPath);

    void poll();

    void clear();

    bool archived() const;

signals:
    void archiveComplete();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // ARCHIVATOR_H
