#ifndef CPBSPRINTMANAGER_H
#define CPBSPRINTMANAGER_H

#include <QObject>

#include "models/CpbSprintModel.h"

namespace CPB {

class SprintManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SprintModel* sprintModel READ sprintModel CONSTANT)
    Q_PROPERTY(int currentSprint READ currentSprint WRITE setCurrentSprint NOTIFY currentSprintChanged)

public:
    explicit SprintManager(QObject *parent = nullptr);

    SprintModel *sprintModel() const;

    int currentSprint() const;
    void setCurrentSprint(int currentSprint);

signals:
    void currentSprintChanged(int currentSprint);

private:
    SprintModel* m_sprintModel;
    int m_currentSprint;
};

}

#endif // CPBSPRINTMANAGER_H
