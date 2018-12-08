#include "CpbStoryManager.h"

#include "CpbUtils.h"

using namespace CPB;

namespace  {
const QString STORY_TITLE_TEMPLATE ("Story %0");
const int MIN_ROW_COUNT = 1;
const int MAX_ROW_COUNT = 10;
}

StoryManager::StoryManager(QObject *parent) :
    QObject(parent)
{
}

StoryManager::~StoryManager()
{
}

QString StoryManager::newStoryName(Sprint* parentSprint) const
{
    return Utils::generateEntityName<StoryModel>(STORY_TITLE_TEMPLATE, parentSprint->storyModel());
}

void StoryManager::createStory(const QString& storyTitle, Sprint* parentSprint)
{
    if (parentSprint == nullptr || storyTitle.isNull() || storyTitle.isEmpty())
    {
        return;
    }

    Story* newStory = new Story(storyTitle, parentSprint);
    if (parentSprint->storyModel()->append(newStory))
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
    if (story == nullptr || story->rowCount() == MAX_ROW_COUNT)
    {
        return;
    }

    story->parentSprint()->storyModel()->update(story, story->rowCount() + 1, StoryModel::RowCountRole);
    emit storyRowChanged(story->parentSprint()->title(), story);
}

void StoryManager::removeRow(Story *story)
{
    if (story == nullptr || story->rowCount() == MIN_ROW_COUNT)
    {
        return;
    }

    story->parentSprint()->storyModel()->update(story, story->rowCount() - 1, StoryModel::RowCountRole);
    emit storyRowChanged(story->parentSprint()->title(), story);
}

int StoryManager::minRowCount() const
{
    return MIN_ROW_COUNT;
}

int StoryManager::maxRowCount() const
{
    return MAX_ROW_COUNT;
}

int StoryManager::maxTaskRow(Story *story) const
{
    if (story == nullptr)
    {
        return false;
    }

    return story->taskModel()->maxRow();
}
