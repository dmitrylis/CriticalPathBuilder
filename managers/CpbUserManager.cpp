#include "CpbUserManager.h"

using namespace CPB;

UserManager::UserManager(QObject *parent)
    : QObject(parent),
      m_userModel(nullptr)
{
    m_userModel = new UserModel(this);

    // temporary code
    m_userModel->append(new User(0, "Lisin Dmitry", m_userModel));
    m_userModel->append(new User(1, "Christoph Waltz", m_userModel));
    m_userModel->append(new User(2, "Jesse Pinkman", m_userModel));
    m_userModel->append(new User(3, "Walter White", m_userModel));
    m_userModel->append(new User(4, "Dr. Baxter Stockman", m_userModel));
}

UserManager::~UserManager()
{
}

UserModel *UserManager::userModel() const
{
    return m_userModel;
}
