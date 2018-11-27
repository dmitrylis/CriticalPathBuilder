#include "CpbTaskManager.h"

using namespace CPB;

namespace  {
const QString TASK_NAME_TEMPLATE ("Task %0");
}

TaskManager::TaskManager(QObject *parent) :
    QObject(parent),
    m_draggedTask(nullptr)
{
}

TaskManager::~TaskManager()
{
}

Task *TaskManager::draggedTask() const
{
    return m_draggedTask;
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

    QString newTaskName, tempTaskName;
    int taskNumber = 1;
    TaskModel* taskModel = parentStory->taskModel();

    while (taskNumber <= (taskModel->rowCount() + 1))
    {
        tempTaskName = TASK_NAME_TEMPLATE.arg(taskNumber);
        if (taskModel->titleValid(tempTaskName))
        {
            newTaskName = tempTaskName;
            break;
        }
        ++taskNumber;
    }

    Task* newTask = new Task(newTaskName, row, column, parentStory);
    Sprint* parentSprint = parentStory->parentSprint();

    if (taskModel->append(newTask))
    {
        emit taskCreated(parentSprint->title(), parentStory->title(), newTask);
        return;
    }

    newTask->deleteLater();
}

void TaskManager::startDragTask(Task* task)
{
    setDraggedTask(task);
    setHighlight(QRect(task->column(), task->row(), 1, 1));
}

void TaskManager::updateHighlightRow(int mouseY, int cellHeight)
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    int storyRowCount = m_draggedTask->parentStory()->rowCount();

    // minimax
    int newY = qMax(0, qMin(mouseY, storyRowCount * cellHeight - cellHeight));

    // descretization
    newY = (newY + cellHeight / 2) / cellHeight;

    m_highlight.moveTo(m_highlight.x(), newY);
    emit highlightChanged(m_highlight);
}

void TaskManager::updateHighlightColumn(int mouseX, int cellWidth)
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    int storyColumnCount = m_draggedTask->parentStory()->columnCount();

    // minimax
    int newX = qMax(0, qMin(mouseX, storyColumnCount * cellWidth - cellWidth));

    // descretization
    newX = (newX + cellWidth / 2) / cellWidth;

    m_highlight.moveTo(newX, m_highlight.y());
    emit highlightChanged(m_highlight);
}

void TaskManager::stopDragTask()
{
    if (m_draggedTask == nullptr)
    {
        return;
    }

    TaskModel* taskModel = m_draggedTask->parentStory()->taskModel();
    taskModel->update(m_draggedTask, m_highlight.y(), TaskModel::RowRole);
    taskModel->update(m_draggedTask, m_highlight.x(), TaskModel::ColumnRole);

    emit taskMoved(m_draggedTask->parentStory()->parentSprint()->title(), m_draggedTask->parentStory()->title(), m_draggedTask);

    setDraggedTask(nullptr);
    setHighlight(QRect());
}
