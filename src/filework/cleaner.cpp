#include "cleaner.h"

#include <QProcess>

#include <QDebug>

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
        if (m_utilClass.invoke("find", args, findOutput, m_utilClass.projectConfiguration().intSettings["Find files timeout"]))
            addFiles(findOutput, result);
    }

    if (fileType & FILE_REMOVE_TYPE::BUILD)
    {
        if (args.size())
            args.clear();

        args << basePath << "-name" << "BUILD" << "-type" << "d";
        if (m_utilClass.invoke("find", args, findOutput, m_utilClass.projectConfiguration().intSettings["Find files timeout"]))
            addFiles(findOutput, result);
    }

    if (fileType & FILE_REMOVE_TYPE::BIN)
    {
        if (args.size())
            args.clear();

        args << basePath << "-name" << "BIN" << "-type" << "d";
        if (m_utilClass.invoke("find", args, findOutput, m_utilClass.projectConfiguration().intSettings["Find files timeout"]))
            addFiles(findOutput, result);
    }

    if (fileType & FILE_REMOVE_TYPE::LIB)
    {
        if (args.size())
            args.clear();

        args << basePath << "-name" << "*.so*";
        if (m_utilClass.invoke("find", args, findOutput, m_utilClass.projectConfiguration().intSettings["Find files timeout"]))
            addFiles(findOutput, result);
    }

    if (fileType & FILE_REMOVE_TYPE::QMAKE_STASH)
    {
        if (args.size())
            args.clear();

        args << basePath << "-name" << ".qmake.stash";
        if (m_utilClass.invoke("find", args, findOutput, m_utilClass.projectConfiguration().intSettings["Find files timeout"]))
            addFiles(findOutput, result);
    }

    return result;
}

void Cleaner::clearFromMistakes(QStringList &filesToRemove)
{
    // Check if all's good
    QStringList mistakes;
    for (QString & file : filesToRemove)
    {
        if (
            !file.contains("/BIN") &&
            !file.contains("/BUILD") &&
            !file.contains(QRegExp("\\/[^/]+\\.so[^\\/|\\w]+")) &&
            !file.contains("/Makefile") &&
            !file.contains("/.qmake.stash")
        )
        {
            qDebug() << "[REMOVE CHECK] Invalid file:[" << file << "]";
            mistakes << file;
        }
    }

    for (QString & miss : mistakes)
    {
        filesToRemove.removeOne(miss);
    }
}

void Cleaner::removeFiles(const QStringList &  filesToRemove)
{
    for (const QString & file : filesToRemove)
    {
        qDebug() << "[CLEANER] Removing file or a dir:" << file;
        system(QString("rm \"%1\" -R").arg(file).toUtf8().data());
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
