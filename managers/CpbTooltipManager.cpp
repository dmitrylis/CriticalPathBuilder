#include "CpbTooltipManager.h"

using namespace CPB;

namespace  {
const QString TASK_DESCRIPTION_TOOLTIP ("qrc:/qml/tooltips/CpbTaskDescriptionTooltip.qml");
const QString CALENDAR_TOOLTIP ("qrc:/qml/tooltips/CpbCalendarTooltip.qml");
const QString EMPLOYE_TOOLTIP ("qrc:/qml/tooltips/CpbEmployeTooltip.qml");
}

TooltipManager::TooltipManager(QObject *parent)
    : BasePopupManager(parent),
      m_senderItem(nullptr),
      m_alignment(TooltipAlignment::None),
      m_position(QPointF(0.0, 0.0)),
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

    m_alignment = TooltipAlignment::None;
    m_position = QPointF(0.0, 0.0);
    emit positionChanged();

    m_senderItem = nullptr;
    emit senderItemChanged();
}

void TooltipManager::updateTooltipPosition(QQuickItem* tooltipItem)
{
    if (tooltipItem == nullptr || m_senderItem == nullptr)
    {
        return;
    }

    // map it to the scene coordinate system
    m_position = m_senderItem->mapToScene(calculatePosition(tooltipItem));
    emit positionChanged();
}

void TooltipManager::showTaskDescriptionTooltip(QQuickItem* senderItem, const QVariant& task)
{
    show(senderItem, TASK_DESCRIPTION_TOOLTIP, TooltipAlignment::LeftAbove, true, QVariantList() << task);
}

void TooltipManager::showCalendarTooltip(QQuickItem *senderItem, const QDate& sourceDate)
{
    show(senderItem, CALENDAR_TOOLTIP, TooltipAlignment::CenterAbove, false, QVariantList() << sourceDate);
}

void TooltipManager::showEmployeTooltip(QQuickItem *senderItem)
{
    show(senderItem, EMPLOYE_TOOLTIP, TooltipAlignment::CenterBelow, false);
}

void TooltipManager::show(QQuickItem *senderItem, const QString &path, TooltipAlignment alignment, bool autoHide, const QVariantList &data)
{
    if (m_senderItem != senderItem)
    {
        m_senderItem = senderItem;
        emit senderItemChanged();
    }

    m_alignment = alignment;

    if (m_autoHide != autoHide)
    {
        m_autoHide = autoHide;
        emit autoHideChanged();
    }

    BasePopupManager::show(path, data);
}

QPointF TooltipManager::calculatePosition(QQuickItem* tooltipItem)
{
    QPointF position(0.0, 0.0);

    switch (m_alignment)
    {
    case TooltipAlignment::LeftAbove:
        position = QPointF(0.0, -tooltipItem->height());
        break;
    case TooltipAlignment::LeftBelow:
        position = QPointF(0.0, m_senderItem->height());
        break;
    case TooltipAlignment::RightAbove:
        position = QPointF(m_senderItem->width() - tooltipItem->width(), -tooltipItem->height());
        break;
    case TooltipAlignment::RightBelow:
        position = QPointF(m_senderItem->width() - tooltipItem->width(), m_senderItem->height());
        break;
    case TooltipAlignment::CenterAbove:
        position = QPointF((m_senderItem->width() - tooltipItem->width()) * 0.5, -tooltipItem->height());
        break;
    case TooltipAlignment::CenterBelow:
        position = QPointF((m_senderItem->width() - tooltipItem->width()) * 0.5, m_senderItem->height());
        break;
    default:
        qWarning() << "Wrong tooltip alignment";
        break;
    }
    return position;
}
