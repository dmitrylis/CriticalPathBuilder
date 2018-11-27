#include "CpbStoryManager.h"

#include "CpbUtils.h"

using namespace CPB;

namespace  {
const QString STORY_TITLE_TEMPLATE ("Story %0");
}

StoryManager::StoryManager(QObject *parent) :
    QObject(parent)
{
}

StoryManager::~StoryManager()
{
}

QString StoryManager::newStoryName(Sprint* parentSprint)
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
    if (story == nullptr)
    {
        return;
    }

    story->parentSprint()->storyModel()->update(story, story->rowCount() + 1, StoryModel::RowCountRole);
    emit storyRowChanged(story->parentSprint()->title(), story);
}
