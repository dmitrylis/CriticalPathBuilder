#include "CpbStoryManager.h"

using namespace CPB;

namespace  {
const QString STORY_TITLE_TEMPLATE ("Story %0");
}

StoryManager::StoryManager(QObject *parent) :
    QObject(parent)
{
}

void StoryManager::createStory(const QString& storyTitle, Sprint* parentSprint)
{
    if (parentSprint == nullptr || storyTitle.isNull() || storyTitle.isEmpty())
    {
        return;
    }

    StoryModel* const storyModel = parentSprint->storyModel();

//    // TODO move to separate class
//    int storyNumber = 1;
//    QString tempStoryTitle;
//    while (storyNumber <= (storyModel->rowCount() + 1))
//    {
//        tempStoryTitle = STORY_TITLE_TEMPLATE.arg(storyNumber);
//        if (storyModel->titleValid(tempStoryTitle))
//        {
//            storyTitle = tempStoryTitle;
//            break;
//        }
//        ++storyNumber;
//    }

    Story* newStory = new Story(storyTitle, parentSprint);
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
