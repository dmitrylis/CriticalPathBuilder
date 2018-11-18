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

    Story* newStory = new Story(newStoryName, this);

    if (!storyModel->append(newStory))
    {
        newStory->deleteLater();
    }
    xmlSerializer xml;
    xml.xmlAddStory(sprint->title(), newStoryName);
}

void StoryManager::removeStory(Story* story, Sprint* sprint)
{
    if (story == nullptr || sprint == nullptr)
    {
        return;
    }

    if (sprint->storyModel()->remove(story))
    {
        story->deleteLater();
    }
}

void StoryManager::moveStory(int first, int last, Sprint* sprint)
{
    if (sprint == nullptr)
    {
        return;
    }

    sprint->storyModel()->move(first, last);
}
