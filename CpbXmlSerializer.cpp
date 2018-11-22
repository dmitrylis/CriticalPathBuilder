#include "CpbXmlSerializer.h"

using namespace CPB;

namespace {
const QString SPRINTS_TAG ("Sprints");
const QString SPRINT_TAG ("Sprint");
const QString STORIES_TAG ("Stories");
const QString STORY_TAG ("Story");
const QString TASKS_TAG ("Tasks");
const QString TASK_TAG ("Task");
const QString ATTRIBUTE_NAME ("name");
const QString ATTRIBUTE_ROW ("row");
const QString ATTRIBUTE_COLUMN ("column");
const QString ATTRIBUTE_START_DATE ("start_date");
const QString ATTRIBUTE_END_DATE ("end_date");
}

XmlSerializer::XmlSerializer(QObject* parent) : QObject(parent)
{
    mFile.setFileName("struct.xml");
    mFile.open(QIODevice::ReadOnly);
    if (!document.setContent(&mFile))
    {
        mFile.close();
        QDomElement docEle = document.createElement(SPRINTS_TAG);
        document.appendChild(docEle);
        _xmlSaveToFile();
    }
    mFile.close();
}

void XmlSerializer::xmlAddSprint(Sprint* sprint)
{
    QDomElement docElement = document.documentElement();
    QDomElement newSprint = document.createElement(SPRINT_TAG);
    newSprint.setAttribute(ATTRIBUTE_NAME, sprint->title());
    newSprint.setAttribute(ATTRIBUTE_START_DATE, sprint->startDate().toString("dd.MM.yyyy"));
    newSprint.setAttribute(ATTRIBUTE_END_DATE, sprint->endDate().toString("dd.MM.yyyy"));
    QDomElement storyElements = document.createElement(STORIES_TAG);
    docElement.appendChild(newSprint);
    newSprint.appendChild(storyElements);
    _xmlSaveToFile();
}

void XmlSerializer::xmlAddStory(const QString& sprintName, Story* story)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName(SPRINT_TAG);
    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrName = domElement.attributeNode(ATTRIBUTE_NAME);
        if (attrName.value() == sprintName)
        {
            QDomElement stories = domElement.firstChildElement(STORIES_TAG);
            QDomElement newStory = document.createElement(STORY_TAG);
            newStory.setAttribute(ATTRIBUTE_NAME, story->title());
            newStory.setAttribute(ATTRIBUTE_ROW, story->rowCount());
            QDomElement tasksElements = document.createElement(TASKS_TAG);
            stories.appendChild(newStory);
            newStory.appendChild(tasksElements);
            break;
        }
    }
    _xmlSaveToFile();
}

void XmlSerializer::xmlChangeStoryRow(const QString& sprintName, Story* story)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName(SPRINT_TAG);
    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrName = domElement.attributeNode(ATTRIBUTE_NAME);
        if (attrName.value() == sprintName)
        {
            QDomNodeList storyElements = domElement.elementsByTagName(STORY_TAG);
            for (int i = 0; i < storyElements.size(); ++i)
            {
                QDomElement storyEle = storyElements.at(i).toElement();
                QDomAttr attrStoryName = storyEle.attributeNode(ATTRIBUTE_NAME);
                if (attrStoryName.value() == story->title())
                {
                    storyEle.setAttribute(ATTRIBUTE_ROW, story->rowCount());
                }
            }
        }
    }
    _xmlSaveToFile();
}

void XmlSerializer::xmlAddTask(const QString& sprintName, const QString& storyName, Task* task)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName(SPRINT_TAG);
    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrSprintName = domElement.attributeNode(ATTRIBUTE_NAME);
        if (attrSprintName.value() == sprintName)
        {
            QDomNodeList storyElements = domElement.elementsByTagName(STORY_TAG);
            for (int i = 0; i < storyElements.size(); ++i)
            {
                QDomElement storyEle = storyElements.at(i).toElement();
                QDomAttr attrStoryName = storyEle.attributeNode(ATTRIBUTE_NAME);
                if (attrStoryName.value() == storyName)
                {
                    QDomElement tasks = storyEle.firstChildElement(TASKS_TAG);
                    QDomElement newTask = document.createElement(TASK_TAG);
                    newTask.setAttribute(ATTRIBUTE_NAME, task->title());
                    newTask.setAttribute(ATTRIBUTE_ROW, task->row());
                    newTask.setAttribute(ATTRIBUTE_COLUMN, task->column());
                    tasks.appendChild(newTask);
                    break;
                }
            }
        }
    }
    _xmlSaveToFile();
}

void XmlSerializer::_xmlSaveToFile()
{
    mFile.open(QIODevice::WriteOnly);
    QTextStream stream(&mFile);
    stream << document.toString();
    mFile.close();
}

void XmlSerializer::xmlReadFile(SprintModel* sprintModel)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName(SPRINT_TAG);
    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrSprintName = domElement.attributeNode(ATTRIBUTE_NAME);
        QDomAttr attrSprintStDate = domElement.attributeNode(ATTRIBUTE_START_DATE);
        QDomAttr attrSprintEDate = domElement.attributeNode(ATTRIBUTE_END_DATE);
        Sprint* newSprint = new Sprint(attrSprintName.value(), QDate::fromString(attrSprintStDate.value(), "dd.MM.yyyy"),
                                       QDate::fromString(attrSprintEDate.value(), "dd.MM.yyyy"));
        sprintModel->append(newSprint);
        QDomNodeList storyElements = domElement.elementsByTagName(STORY_TAG);
        for (int j = 0; j < storyElements.size(); ++j)
        {
            QDomElement storyElement = storyElements.at(j).toElement();
            QDomAttr attrStoryName = storyElement.attributeNode(ATTRIBUTE_NAME);
            Story* newStory = new Story(attrStoryName.value(), newSprint);
            QDomAttr attrStoryRow = storyElement.attributeNode(ATTRIBUTE_ROW);
            newStory->setRowCount(attrStoryRow.value().toInt());
            newSprint->storyModel()->append(newStory);
            QDomNodeList taskElements = storyElement.elementsByTagName(TASK_TAG);
            for (int k = 0; k < taskElements.size(); ++k)
            {
                QDomElement taskElement = taskElements.at(k).toElement();
                QDomAttr attrTaskName = taskElement.attributeNode(ATTRIBUTE_NAME);
                QDomAttr attrTaskRow = taskElement.attributeNode(ATTRIBUTE_ROW);
                QDomAttr attrTaskColumn = taskElement.attributeNode(ATTRIBUTE_COLUMN);
                Task* newTask = new Task(attrTaskName.value(), attrTaskRow.value().toInt(), attrTaskColumn.value().toInt(), newStory);
                newStory->taskModel()->append(newTask);
            }
        }
    }
}
