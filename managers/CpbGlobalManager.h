#ifndef CPBGLOBALMANAGER_H
#define CPBGLOBALMANAGER_H

#include <QObject>

namespace CPB {

class GlobalManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool appReady READ appReady NOTIFY appReadyChanged)
    Q_PROPERTY(bool showWelcome READ showWelcome NOTIFY showWelcomeChanged)

public:
    explicit GlobalManager(QObject *parent = nullptr);
    ~GlobalManager();

    bool appReady() const;
    bool showWelcome() const;

public slots:
    void setAppReady();
    void setShowWelcome(bool showWelcome);

signals:
    void appReadyChanged(bool appReady);
    void showWelcomeChanged(bool showWelcome);

private:
    bool m_appReady;
    bool m_showWelcome;
};

}

#endif // CPBGLOBALMANAGER_H
