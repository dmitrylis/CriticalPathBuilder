#ifndef CPBSPRINT_H
#define CPBSPRINT_H

#include <QObject>

namespace CPB {

class Sprint : public QObject
{
    Q_OBJECT

public:
    explicit Sprint(const QString& title, QObject *parent = nullptr);

    QString title() const;

signals:

public slots:

private:
    QString mTitle;
};

}

#endif // CPBSPRINT_H
