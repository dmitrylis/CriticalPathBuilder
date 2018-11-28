#ifndef CPBSTORYMANAGER_H
#define CPBSTORYMANAGER_H

#include <QObject>

#include "CpbSprint.h"

namespace CPB {

class StoryManager : public QObject
{
    Q_OBJECT

public:
    explicit StoryManager(QObject *parent = nullptr);
    ~StoryManager();

    Q_INVOKABLE QString newStoryName(Sprint* parentSprint);
    Q_INVOKABLE void createStory(const QString& storyTitle, Sprint* parentSprint);
    Q_INVOKABLE void removeStory(Story* story);
    Q_INVOKABLE void moveStory(int first, int last, Story* story);
    Q_INVOKABLE void addRow(Story* story);

signals:
    void storyCreated(const QString& sprintTitle, Story* story);
    void storyRemoved(const QString& sprintTitle, const QString& storyTitle);
    void storyRowChanged(const QString& sprintTitle, Story* story);
};

}

#endif // CPBSTORYMANAGER_H
