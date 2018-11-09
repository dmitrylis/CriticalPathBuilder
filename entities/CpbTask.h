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
    QString m_title;
    int m_row;
    int m_column;
};

}

#endif // CPBTASK_H
