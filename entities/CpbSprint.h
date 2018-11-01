#ifndef CPBSPRINT_H
#define CPBSPRINT_H

#include <QObject>
#include <models/CpbStoryModel.h>

namespace CPB {

class Sprint : public QObject
{
    Q_OBJECT

public:
    explicit Sprint(const QString& title, QObject *parent = nullptr);

    QString title() const;
    QList<Story*> storyList() const;
    void appendStoryList(Story* story);

signals:

public slots:

private:
    QString mTitle;
    QList<Story*> mStoryList;
};

}

#endif // CPBSPRINT_H
