#ifndef CPBGLOBALMANAGER_H
#define CPBGLOBALMANAGER_H

#include <QObject>

namespace CPB {

class GlobalManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showWelcome READ showWelcome NOTIFY showWelcomeChanged)

public:
    explicit GlobalManager(QObject *parent = nullptr);
    ~GlobalManager();

    bool showWelcome() const;
    Q_INVOKABLE void finishWelcome();

public slots:
    void setShowWelcome(bool showWelcome);

signals:
    void showWelcomeChanged(bool showWelcome);

private:
    bool m_showWelcome;
};

}

#endif // CPBGLOBALMANAGER_H
