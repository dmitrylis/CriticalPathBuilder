#include "CpbSprint.h"

using namespace CPB;

Sprint::Sprint(const QString& title, const QDate& startDate, const QDate& endDate, QObject *parent)
    : QObject(parent),
      m_title(title),
      m_startDate(startDate),
      m_endDate(endDate),
      m_storyModel(nullptr),
      m_daysModel(nullptr)
{
    m_daysCount = static_cast<int>(m_startDate.daysTo(m_endDate)) + 1;
    m_storyModel = new StoryModel(this);
    m_daysModel = new DaysModel(m_startDate, m_endDate, this);
}

Sprint::~Sprint()
{
}

QString Sprint::title() const
{
    return m_title;
}

QDate Sprint::startDate() const
{
    return m_startDate;
}

QDate Sprint::endDate() const
{
    return m_endDate;
}

int Sprint::daysCount() const
{
    return m_daysCount;
}

StoryModel* Sprint::storyModel() const
{
    return m_storyModel;
}

DaysModel* Sprint::daysModel() const
{
    return m_daysModel;
}
