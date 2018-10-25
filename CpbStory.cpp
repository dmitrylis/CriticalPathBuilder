#include "CpbStory.h"

using namespace CPB;

Story::Story(const QString& title, QObject *parent)
    : QObject(parent),
      mTitle(title)
{

}

QString Story::title() const
{
    return mTitle;
}

