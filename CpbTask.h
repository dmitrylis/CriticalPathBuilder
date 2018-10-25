#ifndef CPBTASK_H
#define CPBTASK_H

#include <QObject>

namespace CPB {

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(const QString& title, QObject *parent = nullptr);

    QString title() const;

signals:

public slots:

private:
    QString mTitle;
    int mRow;
    int mColumn;
};

}

#endif // CPBTASK_H
