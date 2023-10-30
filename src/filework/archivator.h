#ifndef ARCHIVATOR_H
#define ARCHIVATOR_H

#include <memory>
#include <QString>

namespace FileWork
{

class Archivator
{
public:
    Archivator();
    ~Archivator();

    bool addFile(const QString & path);
    bool addProject(const QString & projectDirPath);

    bool archive();

    void poll();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // ARCHIVATOR_H
