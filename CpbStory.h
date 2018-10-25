#ifndef CPBSTORY_H
#define CPBSTORY_H

#include <QObject>
#include "CpbTaskModel.h"

namespace CPB {

class Story : public QObject
{
    Q_OBJECT

public:
    explicit Story(const QString& title, QObject *parent = nullptr);

    QString title() const;

signals:

public slots:

private:
    QString mTitle;
    int mRow;
    TaskModel mTaskModel;
};

}

#endif // CPBSTORY_H
