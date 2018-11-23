#ifndef CPBENTITYMODEL_H
#define CPBENTITYMODEL_H

#include <QAbstractListModel>

namespace CPB {

// auxiliary class where it is possible to add properties, signals and slots
// because it's impossible to do it in template class
class EntityModelPrivate : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

public:
    explicit EntityModelPrivate(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    virtual ~EntityModelPrivate() {}

signals:
    void rowCountChanged();
};

template <class T>
class EntityModel : public EntityModelPrivate
{
public:
    explicit EntityModel(QObject *parent = nullptr) : EntityModelPrivate(parent) {}
    virtual ~EntityModel() {}

    // overrides
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // custom
    bool append(T *entity);
    bool remove(T *entity);
    void update(T *entity, const QVariant &value, int role = Qt::EditRole);
    void move(int from, int to);
    bool titleValid(const QString& title);

protected:
    QList<T*> m_entityList;
};

template<class T>
QVariant EntityModel<T>::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

template<class T>
int EntityModel<T>::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }

    return m_entityList.count();
}

template<class T>
bool EntityModel<T>::append(T *entity)
{
    if (entity == nullptr || m_entityList.contains(entity))
    {
        return false;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_entityList.append(entity);
    endInsertRows();

    emit rowCountChanged();

    return true;
}

template<class T>
bool EntityModel<T>::remove(T *entity)
{
    if (entity == nullptr || !m_entityList.contains(entity))
    {
        return false;
    }

    const int entityIndex = m_entityList.indexOf(entity);

    beginRemoveRows(QModelIndex(), entityIndex, entityIndex);
    m_entityList.removeAt(entityIndex);
    endRemoveRows();

    emit rowCountChanged();

    return true;
}

template<class T>
void EntityModel<T>::update(T *entity, const QVariant &value, int role)
{
    if (entity == nullptr || !m_entityList.contains(entity))
    {
        return;
    }

    const int entityIndex = m_entityList.indexOf(entity);
    const QModelIndex modelIndex = index(entityIndex);

    if (setData(modelIndex, value, role))
    {
        emit dataChanged(modelIndex, modelIndex, { role });
    }
}

template<class T>
void EntityModel<T>::move(int from, int to)
{
    if (from == to)
    {
        return;
    }

    // http://doc.qt.io/qt-5/qabstractitemmodel.html#beginMoveRows
    // some lifehack
    int moveTo = to;
    if (to > from) {
        ++moveTo;
    }

    beginMoveRows(QModelIndex(), from, from, QModelIndex(), moveTo);
    m_entityList.move(from, to);
    endMoveRows();
}

template<class T>
bool EntityModel<T>::titleValid(const QString &title)
{
    if (title.isNull() || title.isEmpty())
    {
        return false;
    }

    auto result = std::find_if(m_entityList.begin(), m_entityList.end(), [title] (const T* const entity) {
        return entity->title().compare(title, Qt::CaseInsensitive) == 0;
    });

    return result == m_entityList.end();
}

}

#endif // CPBENTITYMODEL_H
