#include "CpbTask.h"

using namespace CPB;

Task::Task(const QString& title, QObject *parent)
    : QObject(parent),
      m_title(title)
{
}

Task::~Task()
{
}

QString Task::title() const
{
    return m_title;
}

int Task::row() const
{
    return m_row;
}

int Task::column() const
{
    return m_column;
}
