#ifndef CPBTASKMODEL_H
#define CPBTASKMODEL_H

#include <QAbstractListModel>
#include "CpbTask.h"

namespace CPB {

class TaskModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum TaskRoles {
        TitleRole = Qt::UserRole + 1,
        ParentStoryRole,
        RowRole,
        ColumnRole,
        DaysRole
    };
    Q_ENUM(TaskRoles)

    explicit TaskModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Task*> mTaskList;
};

}

#endif // CPBTASKMODEL_H
