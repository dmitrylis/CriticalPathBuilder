#ifndef CPBSTORYMODEL_H
#define CPBSTORYMODEL_H

#include "CpbEntityModel.h"
#include "CpbStory.h"

namespace CPB {

class StoryModel : public EntityModel<Story>
{
    Q_OBJECT

public:
    enum StoryRoles {
        StoryRole = Qt::UserRole + 1,
        TitleRole,
        OwnerRole,
        RowCountRole,
        ColumnCountRole,
        TaskModelRole
    };
    Q_ENUM(StoryRoles)

    explicit StoryModel(QObject *parent = nullptr);
    ~StoryModel() override;

    // overrides
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
};

}

#endif // CPBSTORYMODEL_H
