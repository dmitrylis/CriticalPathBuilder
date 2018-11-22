#ifndef SPRINTMODEL_H
#define SPRINTMODEL_H

#include "CpbEntityModel.h"
#include "CpbSprint.h"

namespace CPB {

class SprintModel : public EntityModel<Sprint>
{
    Q_OBJECT

public:
    enum SprintRoles {
        SprintRole = Qt::UserRole + 1,
        TitleRole,
        StartDateRole,
        EndDateRole,
        StoryModelRole
    };
    Q_ENUM(SprintRoles)

    explicit SprintModel(QObject *parent = nullptr);
    ~SprintModel() override;

    // overrides
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // custom
    Sprint* previous(Sprint *sprint) const;
    Sprint* next(Sprint *sprint) const;
    Sprint* first() const;

protected:
    bool isValidIndex(int index) const;
};

}

#endif // SPRINTMODEL_H
