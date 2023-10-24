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

    void poll();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // PROJECTDIRECTORYFILEINTERFACE_H
