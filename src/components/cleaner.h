#ifndef CLEANER_H
#define CLEANER_H

#include <QString>

#include "utilfunctionclass.h"
#include "projectsettings.h"

namespace DependsSearcher
{

enum FILE_REMOVE_TYPE
{
    NO_FILE     = 0b00000,
    MAKEFILE    = 0b00001,
    BUILD       = 0b00010,
    LIB         = 0b00100,
    BIN         = 0b01000,
    QMAKE_STASH = 0b10000
};

class Cleaner // Cleans projects from makefiles and object files, etc
{
public:
    Cleaner();
    ~Cleaner();

    void removeFiles(const QStringList & filesToRemove);

    QStringList getFileList(const QString & basePath, int fileType = FILE_REMOVE_TYPE::NO_FILE);

    static void clearFromMistakes(QStringList &filesToRemove);

private:
    void addFiles(const QString &findOutput, QStringList & resultList);

    UtilFunctionClass & m_utilClass;
};

}

#endif // CLEANER_H
