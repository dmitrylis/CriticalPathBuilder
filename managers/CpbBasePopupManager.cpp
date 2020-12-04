#include "CpbBasePopupManager.h"

using namespace CPB;

BasePopupManager::BasePopupManager(QObject *parent) :
    QObject(parent),
    m_policy(Policy::NonModal)
{
}

BasePopupManager::~BasePopupManager()
{
}

QString BasePopupManager::path() const
{
    return m_path;
}

BasePopupManager::Policy BasePopupManager::policy() const
{
    return m_policy;
}

QVariantList BasePopupManager::data() const
{
    return m_data;
}

void BasePopupManager::hide()
{
    m_path.clear();
    emit pathChanged();

    m_policy = Policy::NonModal;
    emit policyChanged();

    m_data.clear();
    emit dataChanged();
}

void BasePopupManager::show(const QString& path, Policy policy, const QVariantList& data)
{
    if (m_data != data)
    {
        m_data = data;
        emit dataChanged();
    }

    if (m_policy != policy)
    {
        m_policy = policy;
        emit policyChanged();
    }

    if (m_path != path)
    {
        m_path = path;
        emit pathChanged();
    }
}
