#ifndef CPBTOOLTIPMANAGER_H
#define CPBTOOLTIPMANAGER_H

#include <QQuickItem>

#include "CpbBasePopupManager.h"

namespace CPB {

class TooltipManager : public BasePopupManager
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ position NOTIFY positionChanged)
    Q_PROPERTY(bool autoHide READ autoHide NOTIFY autoHideChanged)

public:
    explicit TooltipManager(QObject *parent = nullptr);
    ~TooltipManager() override;

    Q_INVOKABLE QQuickItem *senderItem() const;
    QPointF position() const;
    bool autoHide() const;

    Q_INVOKABLE void hide() override;
    Q_INVOKABLE void updateTooltipPosition(QQuickItem* tooltipItem);
    Q_INVOKABLE void showTaskDescriptionTooltip(QQuickItem* senderItem, const QVariant& task);
    Q_INVOKABLE void showCalendarTooltip(QQuickItem* senderItem, const QDate& sourceDate);

signals:
    void positionChanged();
    void autoHideChanged();

protected:
    void show(QQuickItem* senderItem, const QString& path, bool autoHide, const QVariantList& data = QVariantList());

private:
    QQuickItem* m_senderItem;
    QPointF m_position;
    bool m_autoHide;
};

}

#endif // CPBTOOLTIPMANAGER_H
