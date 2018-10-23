#ifndef CPBSTORY_H
#define CPBSTORY_H

#include <QObject>

namespace CPB {

class Story : public QObject
{
    Q_OBJECT

public:
    explicit Story(const QString& title, QObject *parent);

    QString title() const;

signals:

public slots:

private:
    QObject *mParent;
    QString mTitle;
    int mRow;
};

}

#endif // CPBSTORY_H
