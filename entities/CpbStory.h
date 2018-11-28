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

public:
    explicit Story(const QString& title, Sprint* parentSprint);
    ~Story();

    Sprint* parentSprint() const;
    QString title() const;
    int rowCount() const;
    int columnCount() const;
    TaskModel* taskModel() const;

    void setRowCount(int rowCount);

private:
    Sprint* m_parentSprint;
    QString m_title;
    int m_rowCount;
    int m_columnCount;
    TaskModel* m_taskModel;
};

}

#endif // CPBSTORY_H
