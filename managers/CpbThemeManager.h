#ifndef CPBTHEMEMANAGER_H
#define CPBTHEMEMANAGER_H

#include <QObject>
#include <QMap>

// aux
#include <QQmlProperty>

class QQmlEngine;

namespace CPB {

class Theme;

class ThemeManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList themesList READ themesList CONSTANT)

    Q_PROPERTY(QObject* currentTheme READ currentTheme NOTIFY currentThemeChanged)

    Q_PROPERTY(QString themeName READ themeName NOTIFY currentThemeChanged)
    Q_PROPERTY(QObject* colorScheme READ colorScheme NOTIFY currentThemeChanged)
    Q_PROPERTY(QObject* typography READ typography NOTIFY currentThemeChanged)
    Q_PROPERTY(QObject* sizes READ sizes NOTIFY currentThemeChanged)

public:
    explicit ThemeManager(QQmlEngine *engine, QObject *parent = nullptr);

    Q_INVOKABLE void setCurrentTheme(const QString& themeName);

    QStringList themesList() const;
    QObject* currentTheme() const;
    QString themeName() const;
    QObject* colorScheme() const;
    QObject* typography() const;
    QObject* sizes() const;

    // This is an auxiliary method, shouldn't be here
    Q_INVOKABLE QString typeName(QObject* object, const QString& property) const
    {
        return QQmlProperty(object, property).property().typeName();
    }

signals:
    void currentThemeChanged();

private:
    void readThemes(QQmlEngine *engine);

private:
    QMap<QString, Theme*> m_themesMap;
    Theme *m_currentTheme {nullptr};
};

}

#endif // CPBTHEMEMANAGER_H
