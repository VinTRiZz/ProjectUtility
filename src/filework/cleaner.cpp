#include "cleaner.h"

#include <QProcess>

#include <QDebug>

#define FIND_START_TIMEOUT 1000
#define FIND_FINISH_TIMEOUT 5000

using namespace FileWork;

Cleaner::Cleaner()
{

}

Cleaner::~Cleaner()
{

}

QStringList Cleaner::getFileList(const QString &basePath, int fileType)
{
    QStringList result;

    if (fileType & FILE_REMOVE_TYPE::MAKEFILE)
        searchForFiles(basePath, result, "Makefile");

    if (fileType & FILE_REMOVE_TYPE::BUILD)
        searchForFiles(basePath + "/BUILD", result, "f", "-type");

    if (fileType & FILE_REMOVE_TYPE::BIN)
        searchForFiles(basePath + "/BIN", result, "f", "-type");

    if (fileType & FILE_REMOVE_TYPE::LIB)
        searchForFiles(basePath + "/LIB", result, "f", "-type");

    return result;
}

void Cleaner::removeFiles(const QStringList &  filesToRemove)
{
    for (const QString & file : filesToRemove)
    {
        qDebug() << "[CLEANER] Removing file" << file;
        system(QString("rm %1").arg(file).toUtf8().data());
    }
}


bool Cleaner::searchForFiles(const QString &basePath, QStringList & resultList, const QString & filesToFind, const QString & searchType)
{
    QString findOutput;

    QStringList findArgs;
    findArgs << basePath << searchType << filesToFind;

    QProcess findProcess;

    findProcess.setProgram("find");
    findProcess.setArguments(findArgs);

    findProcess.start();
    if (!findProcess.waitForStarted(FIND_START_TIMEOUT))
        return false;

    if (!findProcess.waitForFinished(FIND_FINISH_TIMEOUT))
        return false;

    findOutput = findProcess.readAllStandardOutput();

    if (findOutput.size() < 1)
        return false;

    addFiles(findOutput, resultList);

    return true;
}

void Cleaner::addFiles(const QString &findOutput, QStringList & resultList)
{
    QString buffer;

    int copyFrom = 0,
        copyTo = 0;
    for (; copyTo < findOutput.size(); copyTo++)
    {
        copyTo = findOutput.indexOf(QChar(0x0A), copyFrom);
        if (copyTo != copyFrom)
        {
            buffer.clear();
            buffer.resize(copyTo - copyFrom);
            std::copy(findOutput.data() + copyFrom, findOutput.data() + copyTo, buffer.begin());
            copyFrom = copyTo + 1;
            resultList << buffer;
        }
    }
}
