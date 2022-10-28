#include "CpbGlobalManager.h"

using namespace CPB;


GlobalManager::GlobalManager(QObject *parent) :
    QObject(parent),
    m_appReady(true),
    m_showWelcome(true)
{
}

GlobalManager::~GlobalManager()
{
}

bool GlobalManager::appReady() const
{
    return m_appReady;
}

bool GlobalManager::showWelcome() const
{
    return m_showWelcome;
}

void GlobalManager::setAppReady()
{
    m_appReady = true;
    emit appReadyChanged(true);
}

void GlobalManager::setShowWelcome(bool showWelcome)
{
    if (m_showWelcome != showWelcome)
    {
        m_showWelcome = showWelcome;
        emit showWelcomeChanged(showWelcome);
    }
}

void GlobalManager::resetSettings()
{
    setShowWelcome(true);

    // reset cache
}
