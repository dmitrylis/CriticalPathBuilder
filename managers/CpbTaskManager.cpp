#include "CpbTaskManager.h"

using namespace CPB;

namespace  {
const QString TASK_NAME_TEMPLATE ("Task %0");
}

TaskManager::TaskManager(QObject *parent) :
    QObject(parent)
{

}

void TaskManager::createTask(int row, int column, Story* story)
{
    if (story == nullptr)
    {
        return;
    }

    QString newTaskName, tempTaskName;
    int taskNumber = 1;
    TaskModel* taskModel = story->taskModel();

    while (taskNumber <= (taskModel->rowCount() + 1))
    {
        tempTaskName = TASK_NAME_TEMPLATE.arg(taskNumber);
        if (taskModel->titleValid(tempTaskName))
        {
            newTaskName = tempTaskName;
            break;
        }
        ++taskNumber;
    }

    Task* newTask = new Task(newTaskName, row, column, story);
    Sprint* parentSprint = story->parentSprint();

    if (taskModel->append(newTask))
    {
        emit taskCreated(parentSprint->title(), story->title(), newTask);
        return;
    }

    newTask->deleteLater();
}
