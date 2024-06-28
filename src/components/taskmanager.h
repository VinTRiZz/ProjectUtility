#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "treeItemModel/treeitemmodel.h"

class TaskManager
{
public:
    TaskManager();
    ~TaskManager();

    void setModel(std::shared_ptr<TreeProxy::TreeItemModel> pTaskModel);

    void setSavePath(const QString & path);

    void save();
    void load();

private:
    std::shared_ptr<TreeProxy::TreeItemModel> pModel;
    QString savePath {"./tasks.data"};

    void parseLine(std::string line);
};

#endif // TASKMANAGER_H
