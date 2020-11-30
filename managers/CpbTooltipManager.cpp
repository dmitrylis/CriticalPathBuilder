#include "CpbTooltipManager.h"

using namespace CPB;

namespace  {
const QString TASK_DESCRIPTION_TOOLTIP ("qrc:/qml/tooltips/CpbTaskDescriptionTooltip.qml");
const QString CALENDAR_TOOLTIP ("qrc:/qml/tooltips/CpbCalendarTooltip.qml");
}

TooltipManager::TooltipManager(QObject *parent)
    : BasePopupManager(parent),
      m_senderItem(nullptr),
      m_position(0.0, 0.0),
      m_autoHide(false)
{
}

TooltipManager::~TooltipManager()
{
}

QQuickItem *TooltipManager::senderItem() const
{
    return m_senderItem;
}

QPointF TooltipManager::position() const
{
    return m_position;
}

bool TooltipManager::autoHide() const
{
    return m_autoHide;
}

void TooltipManager::hide()
{
    BasePopupManager::hide();

    m_autoHide = false;
    emit autoHideChanged();

    m_position = QPointF(0.0, 0.0);
    emit positionChanged();
}

void TooltipManager::updateTooltipPosition(QQuickItem* tooltipItem)
{
    if (tooltipItem == nullptr || m_senderItem == nullptr)
    {
        return;
    }

    // calculate local point
    // TODO: it's need to code smart positioning of tooltip depends on window size and sender position
    QPointF source(0.0, -tooltipItem->height());

    // map it to the scene coordinate system
    m_position = m_senderItem->mapToScene(source);
    emit positionChanged();
}

void TooltipManager::showTaskDescriptionTooltip(QQuickItem* senderItem, const QVariant& task)
{
    show(senderItem, TASK_DESCRIPTION_TOOLTIP, true, QVariantList() << task);
}

void TooltipManager::showCalendarTooltip(QQuickItem *senderItem, const QDate& sourceDate)
{
    show(senderItem, CALENDAR_TOOLTIP, false, QVariantList() << sourceDate);
}

void TooltipManager::show(QQuickItem *senderItem, const QString &path, bool autoHide, const QVariantList &data)
{
    if (m_senderItem != senderItem)
    {
        m_senderItem = senderItem;
    }

    if (m_autoHide != autoHide)
    {
        m_autoHide = autoHide;
        emit autoHideChanged();
    }

    BasePopupManager::show(path, data);
}
