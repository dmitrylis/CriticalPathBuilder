#include "CpbSprint.h"
#include "CpbStory.h"

using namespace CPB;

Sprint::Sprint(const QString& title, QObject *parent)
    : QObject(parent),
      mTitle(title)
{

}

QString Sprint::title() const
{
    return mTitle;
}

QList<Story*> Sprint::storyList() const
{
    return mStoryList;
}

void Sprint::appendStoryList(Story* story)
{
    mStoryList.append(story);
}
