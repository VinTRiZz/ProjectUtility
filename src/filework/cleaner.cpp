#include "cleaner.h"

#include <QProcess>

#include <QDebug>

#define FIND_START_TIMEOUT 1000
#define FIND_FINISH_TIMEOUT 5000

using namespace FileWork;

Cleaner::Cleaner() :
    m_utilClass( UtilFunctionClass::getInstance() )
{

}

Cleaner::~Cleaner()
{

}

QStringList Cleaner::getFileList(const QString &basePath, int fileType)
{
    QStringList result;

    QStringList args;
    QString findOutput;

    if (fileType & FILE_REMOVE_TYPE::MAKEFILE)
    {
        args << basePath << "-name" << "Makefile";
        if (m_utilClass.invoke("find", args, findOutput, FIND_FINISH_TIMEOUT))
            addFiles(findOutput, result);

        // searchForFiles(basePath, result, "Makefile");
    }

    if (fileType & FILE_REMOVE_TYPE::BUILD)
    {
        if (args.size())
            args.clear();

        args << basePath + "/BUILD" << "-type" << "f";
        if (m_utilClass.invoke("find", args, findOutput, FIND_FINISH_TIMEOUT))
            addFiles(findOutput, result);

//        searchForFiles(basePath + "/BUILD", result, "f", "-type");
    }

    if (fileType & FILE_REMOVE_TYPE::BIN)
    {
        if (args.size())
            args.clear();

        args << basePath + "/BIN" << "-type" << "f";
        if (m_utilClass.invoke("find", args, findOutput, FIND_FINISH_TIMEOUT))
            addFiles(findOutput, result);

//        searchForFiles(basePath + "/BIN", result, "f", "-type");
    }

    if (fileType & FILE_REMOVE_TYPE::LIB)
    {
        if (args.size())
            args.clear();

        args << basePath + "/LIB" << "-type" << "f";
        if (m_utilClass.invoke("find", args, findOutput, FIND_FINISH_TIMEOUT))
            addFiles(findOutput, result);

//        searchForFiles(basePath + "/LIB", result, "f", "-type");
    }

    if (fileType & FILE_REMOVE_TYPE::QMAKE_STASH)
    {
        if (args.size())
            args.clear();

        args << basePath << "-name" << ".qmake.stash";
        if (m_utilClass.invoke("find", args, findOutput, FIND_FINISH_TIMEOUT))
            addFiles(findOutput, result);

//        searchForFiles(basePath, result, ".qmake.stash");
    }

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
