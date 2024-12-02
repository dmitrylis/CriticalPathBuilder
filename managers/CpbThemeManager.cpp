#include "CpbThemeManager.h"

#include <QDir>
#include <QQmlComponent>

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "CpbTheme.h"

using namespace CPB;

namespace
{

const QLatin1String ThemesDecriptor {":/qml/themes/themes_descriptor.json"};

}


ThemeManager::ThemeManager(QQmlEngine *engine, QObject *parent)
    : QObject {parent}
{
    readThemes(engine);
}

void ThemeManager::setCurrentTheme(const QString &themeName)
{
    if (m_currentTheme && m_currentTheme->name() == themeName)
    {
        return;
    }

    if (m_themesMap.contains(themeName))
    {
        if (m_currentTheme)
        {
            m_currentTheme->setActive(false);
        }

        m_currentTheme = m_themesMap[themeName];
        m_currentTheme->setActive(true);

        emit currentThemeChanged();
    }
    else
    {
        qWarning() << "Using unknown theme name: " << themeName;
    }
}

QStringList ThemeManager::themesList() const
{
    return m_themesMap.keys();
}

QObject* ThemeManager::currentTheme() const
{
    return m_currentTheme;
};

QString ThemeManager::themeName() const
{
    return m_currentTheme->name();
};

QObject* ThemeManager::colorScheme() const
{
    return m_currentTheme->colorScheme();
};

QObject* ThemeManager::typography() const
{
    return m_currentTheme->typography();
};

QObject* ThemeManager::sizes() const
{
    return m_currentTheme->sizes();
};

void ThemeManager::readThemes(QQmlEngine *engine)
{
    QFile file(ThemesDecriptor);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file:" << file.fileName();
        return;
    }

    const QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    if (jsonDoc.isNull())
    {
        qWarning() << "Failed to parse JSON data";
        return;
    }

    file.close();

    const QJsonObject jsonObj = jsonDoc.object();
    const QString defaultTheme = jsonObj.value("default_theme").toString();
    const QJsonArray themesArray = jsonObj.value("themes").toArray();

    for (const QJsonValue& themeValue : themesArray)
    {
        Theme* newTheme = new Theme(themeValue.toObject(), engine, this);

        if (!m_themesMap.contains(newTheme->name()))
        {
            m_themesMap.insert(newTheme->name(), newTheme);

            if (defaultTheme.compare(newTheme->name(), Qt::CaseInsensitive) == 0)
            {
                setCurrentTheme(newTheme->name());
            }
        }
        else
        {
            qWarning() << "Duplicated theme name in configuration:" << newTheme->name();
        }
    }

    if (m_currentTheme == nullptr && !m_themesMap.isEmpty())
    {
        qInfo() << "Default ambiance hasn't specified.";
        setCurrentTheme(m_themesMap.cbegin().key());
    }
}
