#ifndef CPBTOOLTIPMANAGER_H
#define CPBTOOLTIPMANAGER_H

#include <QQuickItem>

#include "CpbBasePopupManager.h"

namespace CPB {

class TooltipManager : public BasePopupManager
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* senderItem READ senderItem NOTIFY senderItemChanged)
    Q_PROPERTY(QPointF position READ position NOTIFY positionChanged)
    Q_PROPERTY(bool autoHide READ autoHide NOTIFY autoHideChanged)

public:
    enum TooltipAlignment
    {
        None = 0,
        LeftAbove,
        LeftBelow,
        RightAbove,
        RightBelow,
        CenterAbove,
        CenterBelow
    };
    Q_ENUM(TooltipAlignment)

    explicit TooltipManager(QObject *parent = nullptr);
    ~TooltipManager() override;

    QQuickItem *senderItem() const;
    QPointF position() const;
    bool autoHide() const;

    Q_INVOKABLE void hide() override;
    Q_INVOKABLE void updateTooltipPosition(QQuickItem* tooltipItem);
    Q_INVOKABLE void showTaskDescriptionTooltip(QQuickItem* senderItem, const QVariant& task);
    Q_INVOKABLE void showCalendarTooltip(QQuickItem* senderItem, const QDate& sourceDate);
    Q_INVOKABLE void showEmployeTooltip(QQuickItem* senderItem);

signals:
    void senderItemChanged();
    void positionChanged();
    void autoHideChanged();

protected:
    void show(QQuickItem* senderItem, const QString& path, TooltipAlignment alignment = TooltipAlignment::LeftAbove, bool autoHide = true, const QVariantList& data = QVariantList());
    QPointF calculatePosition(QQuickItem* tooltipItem);

private:
    QQuickItem* m_senderItem;
    TooltipAlignment m_alignment;
    QPointF m_position;
    bool m_autoHide;
};

}

#endif // CPBTOOLTIPMANAGER_H
