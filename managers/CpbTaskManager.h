#ifndef CPBTASKMANAGER_H
#define CPBTASKMANAGER_H

#include <QObject>
#include <QRect>

#include "CpbStory.h"
#include "CpbSprint.h"

namespace CPB {

class TaskManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Task* draggedTask READ draggedTask NOTIFY draggedTaskChanged)
    Q_PROPERTY(QRect highlight READ highlight NOTIFY highlightChanged)
    Q_PROPERTY(bool dropPossible READ dropPossible NOTIFY dropPossibleChanged)

public:
    enum GestureType {
        GestureNone = 0,
        GestureMove,
        GestureResizeX
    };
    Q_ENUM(GestureType)

public:
    explicit TaskManager(QObject *parent = nullptr);
    virtual ~TaskManager();

    Task* draggedTask() const;
    GestureType gestureType() const;
    QRect highlight() const;
    bool dropPossible() const;

    void setDraggedTask(Task* task);
    void setGestureType(GestureType gestureType);
    void setHighlight(const QRect& rect);
    void setDropPossible(bool dropPossible);

    Q_INVOKABLE QString newTaskName(Story* parentStory) const;
    Q_INVOKABLE void createTask(Story* parentStory, const QString& taskTitle, const QString& taskOwner, int row, int column);
    Q_INVOKABLE void removeTask(Task* task);
    Q_INVOKABLE void startDragTask(Task* task, GestureType gestureType);
    Q_INVOKABLE void updateHighlightRow(int mouseX, int cellWidth);
    Q_INVOKABLE void updateHighlightColumn(int mouseY, int cellHeight);
    Q_INVOKABLE void updateHighlightDaysCount(int mouseX, int celTitlelWidth);
    Q_INVOKABLE void stopDragTask();

signals:
    void draggedTaskChanged() const;
    void gestureTypeChanged() const;
    void highlightChanged() const;
    void dropPossibleChanged() const;

    void taskCreated(const QString& sprintTitle, const QString& storyTitle, Task* task) const;
    void taskMoved(const QString& sprintTitle, const QString& storyTitle, Task* task);
    void taskRemoved(const QString& sprintTitle, const QString& storyTitle, const QString& taskTitle);
    void taskDaysCountChanged(const QString& sprintTitle, const QString& storyTitle, Task* task) const;

protected slots:
    void changeCursorShape();

private:
    void checkDropPossible();

private:
    Task* m_draggedTask;
    GestureType m_gestureType;
    QRect m_highlight;
    bool m_dropPossible;
};

}

#endif // CPBTASKMANAGER_H
