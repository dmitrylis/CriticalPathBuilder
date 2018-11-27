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

    void setDraggedTask(Task* task);
    void setGestureType(GestureType gestureType);
    void setHighlight(const QRect& rect);


    Q_INVOKABLE void createTask(int row, int column, Story* parentStory);
    Q_INVOKABLE void startDragTask(Task* task, GestureType gestureType);
    Q_INVOKABLE void updateHighlightRow(int mouseX, int cellWidth);
    Q_INVOKABLE void updateHighlightColumn(int mouseY, int cellHeight);
    Q_INVOKABLE void updateHighlightDaysCount(int mouseX, int cellWidth);
    Q_INVOKABLE void stopDragTask();

signals:
    void draggedTaskChanged(Task* draggedTask) const;
    void gestureTypeChanged(GestureType gestureType) const;
    void highlightChanged(QRect highlight) const;
    void taskCreated(const QString& sprintTitle, const QString& storyTitle, Task* task) const;
    void taskMoved(const QString& sprintTitle, const QString& storyTitle, Task* task);
    void taskRemoved(const QString& sprintTitle, const QString& storyTitle, const QString& taskTitle);
    void taskDaysCountChanged(const QString& sprintTitle, const QString& storyTitle, Task* task) const;

protected slots:
    void changeCursorShape(GestureType gestureType);

private:
    Task* m_draggedTask;
    GestureType m_gestureType;
    QRect m_highlight;
};

}

#endif // CPBTASKMANAGER_H
