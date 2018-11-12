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
        TitleRole = Qt::UserRole + 1,
        RowRole,
        ColumnRole,
        DaysRole
    };
    Q_ENUM(TaskRoles)

    explicit TaskModel(QObject *parent = nullptr);
    ~TaskModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
};

}

#endif // CPBTASKMODEL_H
