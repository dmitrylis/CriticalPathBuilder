#include "CpbTaskManager.h"

#include "CpbUtils.h"

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
    m_highlight(QRect()),
    m_dropPossible(true)
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

bool TaskManager::dropPossible() const

{
    return m_dropPossible;
}

void TaskManager::setDraggedTask(Task* task)
{
    if (m_draggedTask == task)
    {
        return;
    }

    m_draggedTask = task;
    emit draggedTaskChanged();
}

void TaskManager::setGestureType(TaskManager::GestureType gestureType)
{
    if (m_gestureType == gestureType)
    {
        return;
    }

    m_gestureType = gestureType;
    emit gestureTypeChanged();
}

void TaskManager::setHighlight(const QRect& rect)
{
    if (m_highlight == rect)
    {
        return;
    }

    m_highlight = rect;
    emit highlightChanged();
}

void TaskManager::setDropPossible(bool dropPossible)
{
    if (m_dropPossible == dropPossible)
    {
        return;
    }

    m_dropPossible = dropPossible;
    emit dropPossibleChanged();
}

QString TaskManager::newTaskName(Story* parentStory)
{
    return Utils::generateEntityName<TaskModel>(TASK_TITLE_TEMPLATE, parentStory->taskModel());
}

void TaskManager::createTask(const QString& taskTitle, int row, int column, Story* parentStory)
{
    if (parentStory == nullptr || taskTitle.isNull() || taskTitle.isEmpty())
    {
        return;
    }

    Task* newTask = new Task(taskTitle, row, column, parentStory);

    if (parentStory->taskModel()->append(newTask))
    {
        emit taskCreated(parentStory->parentSprint()->title(), parentStory->title(), newTask);
        return;
    }

    newTask->deleteLater();
}

void TaskManager::removeTask(Task* task)
{
    if (task == nullptr)
    {
        return;
    }

    if (task->parentStory()->taskModel()->remove(task))
    {
        emit taskRemoved(task->parentStory()->parentSprint()->title(), task->parentStory()->title(), task->title());
        task->deleteLater();
    }
}

void TaskManager::startDragTask(Task* task, GestureType gestureType)
{
    setDraggedTask(task);
    setGestureType(gestureType);
    setHighlight(QRect(task->column(), task->row(), task->daysCount(), 1));
    setDropPossible(true);
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

    // update highlight
    m_highlight.moveTo(m_highlight.x(), newRow);
    emit highlightChanged();

    // check for drop
    checkDropPossible();
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

    // update highlight
    m_highlight.moveTo(newColumn, m_highlight.y());
    emit highlightChanged();

    // check for drop
    checkDropPossible();
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

    // update highlight
    m_highlight.setWidth(newDaysCount);
    emit highlightChanged();

    // check for drop
    checkDropPossible();
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

    QRect dropRect = dropPossible() ? m_highlight
                                    : QRect(draggedTask->column(), draggedTask->row(), draggedTask->daysCount(), 1);

    // update it in model from stored pointer
    switch (gestureType()) {
    case TaskManager::GestureMove:
        taskModel->update(draggedTask, dropRect.y(), TaskModel::RowRole);
        taskModel->update(draggedTask, dropRect.x(), TaskModel::ColumnRole);
        emit taskMoved(draggedTask->parentStory()->parentSprint()->title(),
                       draggedTask->parentStory()->title(),
                       draggedTask);
        break;
    case TaskManager::GestureResizeX:
        taskModel->update(draggedTask, dropRect.width(), TaskModel::DaysCountRole);
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
    setDropPossible(true);
}

void TaskManager::changeCursorShape()
{
    switch (gestureType()) {
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

void TaskManager::checkDropPossible()
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    TaskModel* taskModel = m_draggedTask->parentStory()->taskModel();
    for (int row = m_highlight.y(), column = m_highlight.x(); column < m_highlight.x() + m_highlight.width(); ++column)
    {
        Task* task = taskModel->task(row, column);
        if (task != nullptr && task != m_draggedTask)
        {
            setDropPossible(false);
            return;
        }
    }

    setDropPossible(true);
}
