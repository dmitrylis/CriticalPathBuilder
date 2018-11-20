#include "CpbDaysModel.h"

#include <QLocale>

CPB::DaysModel::DaysModel(const QDate& startDate, const QDate& endDate, QObject *parent)
    : QAbstractListModel(parent)
{
    int days = static_cast<int>(startDate.daysTo(endDate));
    QDate iDay;
    for (int i = 0; i < days; ++i)
    {
        iDay = startDate.addDays(i);
        m_daysModelList.append(iDay);
    }
}

CPB::DaysModel::~DaysModel()
{
}

QVariant CPB::DaysModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

int CPB::DaysModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }

    return m_daysModelList.count();
}

QVariant CPB::DaysModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const QDate date = m_daysModelList[index.row()];
    switch(role) {
    case DaysModelRoles::DayNumberRole:
        return date.day();
    case DaysModelRoles::DayNameRole:
        return QLocale().dayName(date.dayOfWeek());
    case DaysModelRoles::MonthNameRole:
        return QLocale().monthName(date.month());
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> CPB::DaysModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DaysModelRoles::DayNumberRole] = "dayNumberRole";
    roles[DaysModelRoles::DayNameRole] = "dayNameRole";
    roles[DaysModelRoles::MonthNameRole] = "monthNameRole";
    return roles;
}
