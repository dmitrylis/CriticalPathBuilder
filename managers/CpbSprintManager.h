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
    Q_INVOKABLE void createSprint(const QString& sprintName, const QString& startDate, const QString& endDate);
    Q_INVOKABLE void createSprint(const QString& sprintName, const QString& startDate, const qint32& duration);
    Q_INVOKABLE void removeSprint(Sprint* sprint);
    Q_INVOKABLE void moveSprint(int from, int to);

public slots:
    void onModelLoaded();

signals:
    void currentSprintChanged(Sprint* sprint);
    void sprintCreated(Sprint* sprint);
    void sprintRemoved(const QString& sprintName);

private:
    SprintModel* m_sprintModel;
    Sprint* m_currentSprint;
};

}

#endif // CPBSPRINTMANAGER_H
