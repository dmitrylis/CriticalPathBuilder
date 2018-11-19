#ifndef CPBSPRINT_H
#define CPBSPRINT_H

#include <QObject>

#include "CpbStoryModel.h"

namespace CPB {

class Sprint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(StoryModel* storyModel READ storyModel CONSTANT)

public:
    explicit Sprint(const QString& title, QObject *parent = nullptr);
    virtual ~Sprint();

    QString title() const;
    StoryModel* storyModel() const;

private:
    QString m_title;
    StoryModel* m_storyModel;
};

}

#endif // CPBSPRINT_H
