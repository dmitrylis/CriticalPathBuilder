#include "CpbTaskManager.h"

#include <QGuiApplication>
#include <QCursor>

using namespace CPB;

namespace  {
const QString TASK_TITLE_TEMPLATE ("Task %0");
}

TaskManager::TaskManager(QObject *parent) :
    QObject(parent),
    m_draggedTask(nullptr),
    m_gestureType(TaskManager::GestureNone),
    m_highlight(QRect())
{
    // need to move it somewhere outside this class... or no
    connect(this, &TaskManager::gestureTypeChanged, this, &TaskManager::changeCursorShape);
}

TaskManager::~TaskManager()
{
}

Task *TaskManager::draggedTask() const
{
    return m_draggedTask;
}

TaskManager::GestureType TaskManager::gestureType() const
{
    return m_gestureType;
}

QRect TaskManager::highlight() const
{
    return m_highlight;
}

void TaskManager::setDraggedTask(Task* task)
{
    if (m_draggedTask == task)
    {
        return;
    }

    m_draggedTask = task;
    emit draggedTaskChanged(m_draggedTask);
}

void TaskManager::setGestureType(TaskManager::GestureType gestureType)
{
    if (m_gestureType == gestureType)
    {
        return;
    }

    m_gestureType = gestureType;
    emit gestureTypeChanged(m_gestureType);
}

void TaskManager::setHighlight(const QRect& rect)
{
    if (m_highlight == rect)
    {
        return;
    }

    m_highlight = rect;
    emit highlightChanged(m_highlight);
}

void TaskManager::createTask(int row, int column, Story* parentStory)
{
    if (parentStory == nullptr)
    {
        return;
    }

    QString newTaskTitle, tempTaskTitle;
    int taskNumber = 1;
    TaskModel* taskModel = parentStory->taskModel();

    while (taskNumber <= (taskModel->rowCount() + 1))
    {
        tempTaskTitle = TASK_TITLE_TEMPLATE.arg(taskNumber);
        if (taskModel->titleValid(tempTaskTitle))
        {
            newTaskTitle = tempTaskTitle;
            break;
        }
        ++taskNumber;
    }

    Task* newTask = new Task(newTaskTitle, row, column, parentStory);

    if (taskModel->append(newTask))
    {
        emit taskCreated(parentStory->parentSprint()->title(), parentStory->title(), newTask);
        return;
    }

    newTask->deleteLater();
}

void TaskManager::startDragTask(Task* task, GestureType gestureType)
{
    setDraggedTask(task);
    setGestureType(gestureType);
    setHighlight(QRect(task->column(), task->row(), task->daysCount(), 1));
}

void TaskManager::updateHighlightRow(int mouseY, int cellHeight)
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    int storyRowCount = m_draggedTask->parentStory()->rowCount();

    // descretization
    int newRow = (mouseY + cellHeight / 2) / cellHeight;

    // minimax
    newRow = qMax(0, qMin(newRow, storyRowCount - 1));

    m_highlight.moveTo(m_highlight.x(), newRow);
    emit highlightChanged(m_highlight);
}

void TaskManager::updateHighlightColumn(int mouseX, int cellWidth)
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    int storyColumnCount = m_draggedTask->parentStory()->columnCount();

    // descretization
    int newColumn = (mouseX + cellWidth / 2) / cellWidth;

    // minimax
    newColumn = qMax(0, qMin(newColumn, storyColumnCount - m_draggedTask->daysCount()));

    m_highlight.moveTo(newColumn, m_highlight.y());
    emit highlightChanged(m_highlight);
}

void TaskManager::updateHighlightDaysCount(int mouseX, int cellWidth)
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    int storyColumnCount = m_draggedTask->parentStory()->columnCount();

    // descretization
    int newDaysCount = (mouseX + cellWidth / 2) / cellWidth;

    // minimax
    newDaysCount = qMax(1, qMin(newDaysCount, storyColumnCount - m_draggedTask->column()));

    m_highlight.setWidth(newDaysCount);
    emit highlightChanged(m_highlight);
}

void TaskManager::stopDragTask()
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    // store pointers for correct animation of resizing
    Task* draggedTask = m_draggedTask;
    TaskModel* taskModel = m_draggedTask->parentStory()->taskModel();

    // reset dragged task pointer
    setDraggedTask(nullptr);

    // update it in model from stored pointer
    switch (gestureType()) {
    case TaskManager::GestureMove:
        taskModel->update(draggedTask, m_highlight.y(), TaskModel::RowRole);
        taskModel->update(draggedTask, m_highlight.x(), TaskModel::ColumnRole);
        emit taskMoved(draggedTask->parentStory()->parentSprint()->title(),
                       draggedTask->parentStory()->title(),
                       draggedTask);
        break;
    case TaskManager::GestureResizeX:
        taskModel->update(draggedTask, m_highlight.width(), TaskModel::DaysCountRole);
        emit taskDaysCountChanged(draggedTask->parentStory()->parentSprint()->title(),
                                  draggedTask->parentStory()->title(),
                                  draggedTask);
        break;
    case TaskManager::GestureNone:
        break;
    }

    // reset highlight
    setGestureType(TaskManager::GestureNone);
    setHighlight(QRect());
}

void TaskManager::changeCursorShape(GestureType gestureType)
{
    switch (gestureType) {
    case TaskManager::GestureNone:
        QGuiApplication::restoreOverrideCursor();
        return;
    case TaskManager::GestureMove:
        QGuiApplication::setOverrideCursor(Qt::ClosedHandCursor);
        return;
    case TaskManager::GestureResizeX:
        QGuiApplication::setOverrideCursor(Qt::SizeHorCursor);
        return;
    }
}
