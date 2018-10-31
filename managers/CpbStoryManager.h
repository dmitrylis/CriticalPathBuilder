#ifndef CPBSTORYMANAGER_H
#define CPBSTORYMANAGER_H

#include <QObject>

#include "models/CpbStoryModel.h"

namespace CPB {

class StoryManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(StoryModel* storyModel READ storyModel CONSTANT)
    Q_PROPERTY(Story* currentStory READ currentStory WRITE setCurrentStory NOTIFY currentStoryChanged)

public:
    explicit StoryManager(QObject *parent = nullptr);

    StoryModel *storyModel() const;

    Story* currentStory() const;
    void setCurrentStory(Story* story);

    Q_INVOKABLE void addStory();
    Q_INVOKABLE void removeStory(Story* story);
    Q_INVOKABLE void move(int first, int last);

signals:
    void currentStoryChanged(Story* story);

private:
    StoryModel* m_storyModel;
    Story* m_currentStory;
};

}

#endif // CPBSTORYMANAGER_H
