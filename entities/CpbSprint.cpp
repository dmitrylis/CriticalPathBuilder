#include "CpbSprint.h"

using namespace CPB;

Sprint::Sprint(const QString& title, QObject *parent)
    : QObject(parent),
      m_title(title),
      m_storyModel(nullptr)
{
    m_storyModel = new StoryModel(this);
}

Sprint::~Sprint()
{
}

QString Sprint::title() const
{
    return m_title;
}

StoryModel* Sprint::storyModel() const
{
    return m_storyModel;
}
