#include "CpbTheme.h"

#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

using namespace CPB;

Theme::Theme(const QJsonObject& object, QQmlEngine *engine, QObject *parent)
    : QObject {parent}
    , m_engine {engine}
    , m_name {object.value("name").toString()}
    , m_colorSchemePath {object.value("color_scheme").toString()}
    , m_typographyPath {object.value("typography").toString()}
    , m_sizesPath {object.value("sizes").toString()}
{
}

QString Theme::name() const
{
    return m_name;
};

QObject* Theme::colorScheme() const
{
    return m_colorScheme;
};

QObject* Theme::typography() const
{
    return m_typography;
};

QObject* Theme::sizes() const
{
    return m_sizes;
}

bool Theme::active() const
{
    return m_colorScheme != nullptr &&
           m_typography != nullptr &&
           m_sizes != nullptr;
}

void Theme::setActive(bool active)
{
    if (this->active() == active)
    {
        return;
    }

    if (active)
    {
        createObject(m_colorSchemePath, m_colorScheme);
        createObject(m_typographyPath, m_typography);
        createObject(m_sizesPath, m_sizes);
    }
    else
    {
        destroyObject(m_sizes);
        destroyObject(m_typography);
        destroyObject(m_colorScheme);
    }
};

void Theme::createObject(const QString& path, QObject *&object)
{
    if (object)
    {
        qWarning() << "Object already created";
        return;
    }

    QQmlComponent component(m_engine);

    if (path.startsWith(":/"))
    {
        component.loadUrl(QUrl("qrc" + path));
    }
    else
    {
        component.loadUrl(QUrl(path));
    }

    if (component.isError())
    {
        qWarning() << "Component loading error: " << component.errorString();
        return;
    }

    object = component.create(m_engine->rootContext());
}

void Theme::destroyObject(QObject *&object)
{
    if (object)
    {
        object->deleteLater();
        object = nullptr;
    }
}
