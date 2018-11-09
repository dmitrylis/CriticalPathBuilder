#include "CpbTask.h"

using namespace CPB;

Task::Task(const QString& title, QObject *parent)
    : QObject(parent),
      m_title(title)
{

}

QString Task::title() const
{
    return m_title;
}
