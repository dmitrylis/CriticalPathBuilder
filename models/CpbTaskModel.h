#ifndef CPBTASKMODEL_H
#define CPBTASKMODEL_H

#include "CpbEntityModel.h"
#include "CpbTask.h"

namespace CPB {

class TaskModel : public EntityModel<Task>
{
    Q_OBJECT

public:
    enum TaskRoles {
        TaskRole = Qt::UserRole + 1,
        TitleRole,
        RowRole,
        ColumnRole,
        DaysCountRole
    };
    Q_ENUM(TaskRoles)

    explicit TaskModel(QObject *parent = nullptr);
    ~TaskModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
};

}

#endif // CPBTASKMODEL_H
