#ifndef CPBSTORYMANAGER_H
#define CPBSTORYMANAGER_H

#include <QObject>

#include "CpbStoryModel.h"
#include "CpbSprintManager.h"

namespace CPB {

class StoryManager : public QObject
{
    Q_OBJECT

public:
    explicit StoryManager(QObject *parent = nullptr);

    Q_INVOKABLE void createStory(Sprint* sprint);
    Q_INVOKABLE void removeStory(Story* story, Sprint* sprint);
    Q_INVOKABLE void moveStory(int first, int last, Sprint* sprint);

signals:
    void storyCreated(const QString& sprintName, const QString& storyName);
};

}

#endif // CPBSTORYMANAGER_H
