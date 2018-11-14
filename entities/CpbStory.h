#ifndef CPBSTORY_H
#define CPBSTORY_H

#include <QObject>

#include "CpbTaskModel.h"

namespace CPB {

class Story : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TaskModel* taskModel READ taskModel CONSTANT)

public:
    explicit Story(const QString& title, QObject *parent = nullptr);

    QString title() const;
    TaskModel* taskModel() const;

private:
    QString m_title;
    int m_row;
    TaskModel* m_taskModel;
};

}

#endif // CPBSTORY_H
