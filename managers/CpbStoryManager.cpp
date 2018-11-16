#include "CpbStoryManager.h"

using namespace CPB;

namespace  {
const QString STORY_NAME_TEMPLATE ("Story %0");
}

StoryManager::StoryManager(QObject *parent) :
    QObject(parent)
{
}

void StoryManager::createStory(Sprint* sprint)
{
    if (sprint == nullptr)
    {
        return;
    }

    // >> TODO: move to separate class?
    int storyNumber = 1;
    QString newStoryName, tempStoryName;
    StoryModel* storyModel = sprint->storyModel();

    while (storyNumber <= (storyModel->rowCount() + 1))
    {
        tempStoryName = STORY_NAME_TEMPLATE.arg(storyNumber);
        if (storyModel->titleValid(tempStoryName))
        {
            newStoryName = tempStoryName;
            break;
        }
        ++storyNumber;
    }
    // <<

    Story* newStory = new Story(newStoryName, sprint);

    if (!storyModel->append(newStory))
    {
        newStory->deleteLater();
    }
}

void StoryManager::removeStory(Story* story)
{
    if (story == nullptr)
    {
        return;
    }

    Sprint* parentSprint = qobject_cast<Sprint*>(story->parent());
    if (parentSprint == nullptr)
    {
        return;
    }

    if (parentSprint->storyModel()->remove(story))
    {
        story->deleteLater();
    }
}

void StoryManager::moveStory(int first, int last, Story* story)
{
    if (story == nullptr)
    {
        return;
    }

    Sprint* parentSprint = qobject_cast<Sprint*>(story->parent());
    if (parentSprint == nullptr)
    {
        return;
    }

    parentSprint->storyModel()->move(first, last);
}
