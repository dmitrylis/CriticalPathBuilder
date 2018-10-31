#include "CpbStoryManager.h"

using namespace CPB;

namespace  {
const QString STORY_NAME_TEMPLATE ("Story %0");
}

StoryManager::StoryManager(QObject *parent) :
    QObject(parent),
    m_storyModel(nullptr),
    m_currentStory(nullptr)
{
    m_storyModel = new StoryModel(this);
}

StoryModel *StoryManager::storyModel() const
{
    return m_storyModel;
}

Story* StoryManager::currentStory() const
{
    return m_currentStory;
}

void StoryManager::setCurrentStory(Story* story)
{
    if (m_currentStory == story)
    {
        return;
    }

    m_currentStory = story;
    emit currentStoryChanged(m_currentStory);
}

void StoryManager::move(int first, int last)
{
    m_storyModel->move(first, last);
}

void StoryManager::addStory()
{
    const QString newStoryName = STORY_NAME_TEMPLATE.arg(m_storyModel->rowCount() + 1);
    Story* newStory = new Story(newStoryName, this);

    if (m_storyModel->append(newStory))
    {
        setCurrentStory(newStory);
    }
    else
    {
        newStory->deleteLater();
    }
}

void StoryManager::removeStory(Story* story)
{
    Story* storyToSelect = currentStory();
    if (storyToSelect == story)
    {
        storyToSelect = m_storyModel->getPrevious(story);
        if (storyToSelect == nullptr)
        {
            storyToSelect = m_storyModel->getNext(story);
        }
    }

    if (m_storyModel->remove(story))
    {
        setCurrentStory(storyToSelect);
        story->deleteLater();
    }
}
