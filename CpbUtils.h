#ifndef CPBUTILS_H
#define CPBUTILS_H

#include <QString>

namespace CPB {

class Utils
{
public:
    Utils();
    ~Utils();

    template<typename T>
    static QString generateEntityName(const QString& nameTemplate, T* entityModel);
};

template<typename T>
QString Utils::generateEntityName(const QString &nameTemplate, T *entityModel)
{
    int number = 1;
    QString tempTitle;

    while (number <= (entityModel->rowCount() + 1))
    {
        tempTitle = nameTemplate.arg(number);
        if (entityModel->titleValid(tempTitle))
        {
            return tempTitle;
        }
        ++number;
    }

    return tempTitle;
}

}

#endif // CPBUTILS_H
