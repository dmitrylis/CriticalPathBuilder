#ifndef CPBENTITYMODEL_H
#define CPBENTITYMODEL_H

#include <QAbstractListModel>

namespace CPB {

template <class T>
class EntityModel : public QAbstractListModel
{
    //Q_OBJECT

public:
    explicit EntityModel(QObject *parent = nullptr);
    virtual ~EntityModel();

    // overrides
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // custom
    bool append(T *entity);
    bool remove(T *entity);
    void move(int from, int to);
    bool titleValid(const QString& name);

protected:
    QList<T*> m_entityList;
};

template <class T>
EntityModel<T>::EntityModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

template<class T>
EntityModel<T>::~EntityModel()
{
}

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

    return true;
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
bool EntityModel<T>::titleValid(const QString &name)
{
    if (name.isNull() || name.isEmpty())
    {
        return false;
    }

    auto result = std::find_if(m_entityList.begin(), m_entityList.end(), [name] (const T* const entity) {
        return entity->title().compare(name, Qt::CaseInsensitive) == 0;
    });

    return result == m_entityList.end();
}

}

#endif // CPBENTITYMODEL_H
