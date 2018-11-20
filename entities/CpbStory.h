#ifndef CPBSTORY_H
#define CPBSTORY_H

#include <QObject>

#include "CpbTaskModel.h"

namespace CPB {

class Sprint;

class Story : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(TaskModel* taskModel READ taskModel CONSTANT)

public:
    explicit Story(const QString& title, Sprint* parentSprint);
    virtual ~Story();

    Sprint* parentSprint() const;
    QString title() const;
    int row() const;
    TaskModel* taskModel() const;

private:
    Sprint* m_parentSprint;
    QString m_title;
    int m_row;
    TaskModel* m_taskModel;
};

}

#endif // CPBSTORY_H
