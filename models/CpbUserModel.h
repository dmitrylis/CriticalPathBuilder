#ifndef CPBUSERMODEL_H
#define CPBUSERMODEL_H

#include "CpbEntityModel.h"
#include "CpbUser.h"

namespace CPB {

class UserModel : public EntityModel<User>
{
    Q_OBJECT

public:
    enum UserRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };
    Q_ENUM(UserRoles)

    explicit UserModel(QObject *parent = nullptr);
    ~UserModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
};

}

#endif // CPBUSERMODEL_H
