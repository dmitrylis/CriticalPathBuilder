#include "CpbGlobalManager.h"

using namespace CPB;


GlobalManager::GlobalManager(QObject *parent) :
    QObject(parent),
    m_showWelcome(true)
{
}

GlobalManager::~GlobalManager()
{
}

bool GlobalManager::showWelcome() const
{
    return m_showWelcome;
}

void GlobalManager::finishWelcome()
{
    setShowWelcome(false);
}

void GlobalManager::setShowWelcome(bool showWelcome)
{
    if (m_showWelcome != showWelcome)
    {
        m_showWelcome = showWelcome;
        emit showWelcomeChanged(showWelcome);
    }
}
