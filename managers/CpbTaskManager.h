#ifndef CPBTASKMANAGER_H
#define CPBTASKMANAGER_H

#include <QObject>

#include "CpbStory.h"
#include "CpbSprint.h"

namespace CPB {

class TaskManager : public QObject
{
    Q_OBJECT

public:
    explicit TaskManager(QObject *parent = nullptr);

    Q_INVOKABLE void createTask(int row, int column, Story* story);

signals:
    void taskCreated(const QString& sprintName, const QString& storyName, Task* task);
};

}

#endif // CPBTASKMANAGER_H
