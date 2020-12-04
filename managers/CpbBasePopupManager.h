#ifndef CPBBASEPOPUPMANAGER_H
#define CPBBASEPOPUPMANAGER_H

#include <QObject>
#include <QString>
#include <QVariant>

namespace CPB {

class BasePopupManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path NOTIFY pathChanged)
    Q_PROPERTY(Policy policy READ policy NOTIFY policyChanged)
    Q_PROPERTY(QVariantList data READ data NOTIFY dataChanged)

public:
    enum Policy
    {
        NonModal = 0,
        PartiallyModal,
        StrictlyModal
    };
    Q_ENUM(Policy)

    explicit BasePopupManager(QObject *parent = nullptr);
    virtual ~BasePopupManager();

    QString path() const;
    Policy policy() const;
    QVariantList data() const;

    Q_INVOKABLE virtual void hide();

signals:
    void pathChanged();
    void policyChanged();
    void dataChanged();

protected:
    void show(const QString& path, Policy policy, const QVariantList& data = QVariantList());

private:
    QString m_path;
    Policy m_policy;
    QVariantList m_data;
};

}

#endif // CPBBASEPOPUPMANAGER_H
