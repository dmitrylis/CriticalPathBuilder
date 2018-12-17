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
    Q_PROPERTY(QVariantList data READ data NOTIFY dataChanged)

public:
    explicit BasePopupManager(QObject *parent = nullptr);
    virtual ~BasePopupManager();

    QString path() const;
    QVariantList data() const;

    Q_INVOKABLE virtual void hide();

signals:
    void pathChanged();
    void dataChanged();

protected:
    void show(const QString& path, const QVariantList& data = QVariantList());

private:
    QString m_path;
    QVariantList m_data;
};

}

#endif // CPBBASEPOPUPMANAGER_H
