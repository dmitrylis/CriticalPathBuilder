#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QJsonObject>

class QQmlEngine;

namespace CPB {

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QObject* colorScheme READ colorScheme CONSTANT)
    Q_PROPERTY(QObject* typography READ typography CONSTANT)
    Q_PROPERTY(QObject* sizes READ sizes CONSTANT)

public:
    explicit Theme(const QJsonObject& object, QQmlEngine *engine, QObject *parent = nullptr);

    QString name() const;
    QObject* colorScheme() const;
    QObject* typography() const;
    QObject* sizes() const;

    bool active() const;
    void setActive(bool active);

private:
    void createObject(const QString& path, QObject *&object);
    void destroyObject(QObject *&object);

private:
    QQmlEngine *m_engine {nullptr};

    QString m_name;

    QString m_colorSchemePath;
    QObject *m_colorScheme {nullptr};

    QString m_typographyPath;
    QObject *m_typography {nullptr};

    QString m_sizesPath;
    QObject *m_sizes {nullptr};
};

}

#endif // THEME_H
