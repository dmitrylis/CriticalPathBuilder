#ifndef CPBSPRINTMANAGER_H
#define CPBSPRINTMANAGER_H

#include <QObject>

#include "CpbSprintModel.h"
#include "CpbXmlSerializer.h"

namespace CPB {

class SprintManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SprintModel* sprintModel READ sprintModel CONSTANT)
    Q_PROPERTY(Sprint* currentSprint READ currentSprint WRITE setCurrentSprint NOTIFY currentSprintChanged)

public:
    explicit SprintManager(QObject *parent = nullptr);

    SprintModel *sprintModel() const;

    Sprint* currentSprint() const;
    void setCurrentSprint(Sprint* sprint);

    Q_INVOKABLE void createSprint();
    Q_INVOKABLE void removeSprint(Sprint* sprint);
    Q_INVOKABLE void moveSprint(int from, int to);

signals:
    void currentSprintChanged(Sprint* sprint);
    void sprintCreated(Sprint* sprint);

private:
    SprintModel* m_sprintModel;
    Sprint* m_currentSprint;
};

}

#endif // CPBSPRINTMANAGER_H
