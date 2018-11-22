#ifndef CPBTASKMANAGER_H
#define CPBTASKMANAGER_H

#include <QObject>
#include <QRect>

#include "CpbStory.h"

namespace CPB {

class TaskManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Task* draggedTask READ draggedTask NOTIFY draggedTaskChanged)
    Q_PROPERTY(QRect highlight READ highlight NOTIFY highlightChanged)

public:
    explicit TaskManager(QObject *parent = nullptr);
    virtual ~TaskManager();

    Task* draggedTask() const;
    QRect highlight() const;

    void setDraggedTask(Task* task);
    void setHighlight(const QRect& rect);

    Q_INVOKABLE void createTask(int row, int column, Story* story);
    Q_INVOKABLE void startDragTask(Task* task);
    Q_INVOKABLE void updateHighlightRow(int mouseX, int cellWidth);
    Q_INVOKABLE void updateHighlightColumn(int mouseY, int cellHeight);
    Q_INVOKABLE void stopDragTask();

signals:
    void draggedTaskChanged(Task* draggedTask);
    void highlightChanged(QRect highlight);

private:
    Task* m_draggedTask;
    QRect m_highlight;
};

}

#endif // CPBTASKMANAGER_H
