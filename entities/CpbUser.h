#ifndef CPBUSER_H
#define CPBUSER_H

#include <QObject>

namespace CPB {

class User : public QObject
{
    Q_PROPERTY(uint id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_OBJECT

public:
    explicit User(uint id, const QString& name, QObject *parent = nullptr);
    ~User();

    uint id() const;
    QString name() const;

    void setName(const QString &name);

signals:
    void idChanged(uint id);
    void nameChanged(const QString &name);

private:
    uint m_id;
    QString m_name;
};

}

#endif // CPBUSER_H
