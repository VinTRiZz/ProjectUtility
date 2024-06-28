#include "taskmanager.h"

#include "treeItemModel/treeitem.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

void TaskManager::setModel(std::shared_ptr<TreeProxy::TreeItemModel> pTaskModel)
{
    pModel = pTaskModel;
}

void TaskManager::save()
{
    if (!pModel)
        return;
    qDebug() << "\033[33mSaving tasks\033[0m";
    auto taskVect = pModel->getAllChildren();
    if (!taskVect.size())
        return;

    QFile saveFile(savePath);
    saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if (!saveFile.isOpen())
    {
        qDebug() << "\033[31mError opening save file\033[0m";
        return;
    }
    QTextStream saveFileStream(&saveFile);

    const int columnCount = taskVect.first()->columnCount(); // Must be head
    for (std::shared_ptr<TreeProxy::TreeItem> & task : taskVect)
    {
        saveFileStream << task->id() << "#" << task->parentIndex().internalId() << "#";
        for (int i = 0; i < columnCount; i++)
        {
            saveFileStream << task->data(i).toString() << "#";
        }
        saveFileStream << endl;
    }
    saveFile.close();
    qDebug() << "\033[33mTasks saved\033[0m";
}

void TaskManager::load()
{
    qDebug() << "\033[33mLoad tasks\033[0m";

    QFile saveFile(savePath);
    saveFile.open(QIODevice::ReadOnly);
    if (!saveFile.isOpen())
    {
        qDebug() << "\033[31mError opening save file\033[0m";
        return;
    }

    QTextStream saveFileStream(&saveFile);

    while (!saveFileStream.atEnd())
        parseLine( saveFileStream.readLine().toUtf8().data() );

    saveFile.close();
    qDebug() << "\033[33mTasks loaded\033[0m";
}

void TaskManager::parseLine(std::string line)
{
    std::string::iterator dataBegin, dataEnd;
    uint id, pid;
    QVector<QVariant> bufferData;

    // Get id
    dataBegin = std::find(dataBegin, line.end(), '#');
    if (dataBegin == line.end())
        return;
    dataEnd = std::find(dataBegin + 1, line.end(), '#');
    try
    {
        id = std::stoul(std::string(dataBegin, dataEnd));
    } catch (std::invalid_argument & ex)
    {
        qDebug() << "Shit happened with string: \"" << std::string(dataBegin, dataEnd).c_str() << "\"";
    }

    // Get PID
    dataBegin = std::find(dataBegin, line.end(), '#');
    if (dataBegin == line.end())
        return;
    dataEnd = std::find(dataBegin + 1, line.end(), '#');
    try
    {
        pid = std::stoul(std::string(dataBegin, dataEnd));
    } catch (std::invalid_argument & ex)
    {
        qDebug() << "Shit happened with string: \"" << std::string(dataBegin, dataEnd).c_str() << "\"";
    }

    // Get data of item
    while (dataBegin != line.end())
    {
        // Get another line

        // Add to buffer
        bufferData.push_back( std::string(dataBegin, dataEnd).c_str() );
    }

    qDebug() << "Read item: ID" << id << "PID" << pid << "DATA" << bufferData;
    // Add item
//    pModel->addItem(bufferData, id, pid);
}
