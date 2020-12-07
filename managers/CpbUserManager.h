#ifndef CPBUSERMANAGER_H
#define CPBUSERMANAGER_H

#include <QObject>

#include "CpbUserModel.h"

namespace CPB {

class UserManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(UserModel* userModel READ userModel CONSTANT)

public:
    explicit UserManager(QObject *parent = nullptr);
    ~UserManager();

    UserModel* userModel() const;

private:
    UserModel* m_userModel;
};

}

#endif // CPBUSERMANAGER_H
