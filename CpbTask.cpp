#include "CpbTask.h"

using namespace CPB;

Task::Task(const QString& title, QObject *parent)
    : QObject(parent),
      mTitle(title)
{

}

QString Task::title() const
{
    return mTitle;
}
