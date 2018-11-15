#ifndef CPBTASKMANAGER_H
#define CPBTASKMANAGER_H

#include <QObject>

#include "CpbTaskModel.h"
#include "CpbSprintManager.h"

namespace CPB {

class TaskManager : public QObject
{
    Q_OBJECT

public:
    explicit TaskManager(QObject *parent = nullptr);

    Q_INVOKABLE void createTask(Story* story);

};

}

#endif // CPBTASKMANAGER_H
