#include "CpbStoryManager.h"

using namespace CPB;

namespace  {
const QString STORY_NAME_TEMPLATE ("Story %0");
}

StoryManager::StoryManager(QObject *parent) :
    QObject(parent)
{
}

void StoryManager::createStory(const QString& storyName, Sprint* parentSprint)
{
    if (parentSprint == nullptr || storyName.isNull() || storyName.isEmpty())
    {
        return;
    }

    StoryModel* const storyModel = parentSprint->storyModel();

//    // TODO move to separate class
//    int storyNumber = 1;
//    QString tempStoryName;
//    while (storyNumber <= (storyModel->rowCount() + 1))
//    {
//        tempStoryName = STORY_NAME_TEMPLATE.arg(storyNumber);
//        if (storyModel->titleValid(tempStoryName))
//        {
//            storyName = tempStoryName;
//            break;
//        }
//        ++storyNumber;
//    }

    Story* newStory = new Story(storyName, parentSprint);
    if (storyModel->append(newStory))
    {
        emit storyCreated(parentSprint->title(), newStory);
        return;
    }

    newStory->deleteLater();
}

void StoryManager::removeStory(Story* story)
{
    if (story == nullptr)
    {
        return;
    }

    if (story->parentSprint()->storyModel()->remove(story))
    {
        emit storyRemoved(story->parentSprint()->title(), story->title());
        story->deleteLater();
    }
}

void StoryManager::moveStory(int first, int last, Story* story)
{
    if (story == nullptr)
    {
        return;
    }

    story->parentSprint()->storyModel()->move(first, last);
}

void StoryManager::addRow(Story *story)
{
    if (story == nullptr)
    {
        return;
    }

    story->parentSprint()->storyModel()->update(story, story->rowCount() + 1, StoryModel::RowCountRole);
    emit storyRowChanged(story->parentSprint()->title(), story);
}
