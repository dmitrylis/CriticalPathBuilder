#include "CpbBasePopupManager.h"

using namespace CPB;

BasePopupManager::BasePopupManager(QObject *parent) : QObject(parent)
{
}

BasePopupManager::~BasePopupManager()
{
}

QString BasePopupManager::path() const
{
    return m_path;
}

QVariantList BasePopupManager::data() const
{
    return m_data;
}

void BasePopupManager::hide()
{
    m_path.clear();
    emit pathChanged();

    m_data.clear();
    emit dataChanged();
}

void BasePopupManager::show(const QString& path, const QVariantList& data)
{
    if (m_data != data)
    {
        m_data = data;
        emit dataChanged();
    }

    if (m_path != path)
    {
        m_path = path;
        emit pathChanged();
    }
}
