#ifndef SPRINTMODEL_H
#define SPRINTMODEL_H

#include <QAbstractListModel>

#include "entities/CpbSprint.h"

namespace CPB {

class SprintModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SprintRoles {
        TitleRole = Qt::UserRole + 1,
        StartDateRole,
        EndDateRole,
        StoryModelRole
    };
    Q_ENUM(SprintRoles)

    explicit SprintModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Sprint*> mSprintList;
};

}

#endif // SPRINTMODEL_H
