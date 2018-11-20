#ifndef CPBDAYSMODEL_H
#define CPBDAYSMODEL_H

#include <QAbstractListModel>
#include <QDate>

namespace CPB {

class DaysModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DaysModelRoles {
        DayNumberRole = Qt::UserRole + 1,
        DayNameRole,
        MonthNameRole
    };
    Q_ENUM(DaysModelRoles)

    explicit DaysModel(const QDate& startDate, const QDate& endDate, QObject *parent = nullptr);
    virtual ~DaysModel() override;

    // overrides
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<QDate> m_daysModelList;
};

}

#endif // CPBDAYSMODEL_H
