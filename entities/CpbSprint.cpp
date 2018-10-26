#include "CpbSprint.h"

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
