#include "CpbStory.h"

using namespace CPB;

Story::Story(const QString& title, QObject *parent)
    : QObject(parent),
      m_title(title)
{

}

QString Story::title() const
{
    return m_title;
}

