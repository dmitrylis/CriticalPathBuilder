#include "CpbStory.h"

using namespace CPB;

Story::Story(const QString& title, QObject *parent)
    : mParent(parent),
      mTitle(title)
{

}

QString Story::title() const
{
    return mTitle;
}

