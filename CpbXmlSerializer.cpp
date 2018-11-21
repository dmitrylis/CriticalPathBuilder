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
}

xmlSerializer::xmlSerializer(QObject* parent) : QObject(parent)
{
    mFile.setFileName("mydoc.xml");

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

void xmlSerializer::xmlAddSprint(const QString& sprintName)
{
    QDomElement docElement = document.documentElement();
    QDomNodeList sprintsElements = docElement.elementsByTagName(SPRINTS_TAG);
    QDomElement newSprint = document.createElement(SPRINT_TAG);
    newSprint.setAttribute(ATTRIBUTE_NAME, sprintName);
    QDomElement storyElements = document.createElement(STORIES_TAG);

    docElement.appendChild(newSprint);
    newSprint.appendChild(storyElements);

    _xmlSaveToFile();
}

void xmlSerializer::xmlAddStory(const QString& sprintName, const QString& storyName)
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
            newStory.setAttribute(ATTRIBUTE_NAME, storyName);
            QDomElement tasksElements = document.createElement(TASKS_TAG);
            stories.appendChild(newStory);
            newStory.appendChild(tasksElements);
            break;
        }
    }

    _xmlSaveToFile();
}

void xmlSerializer::xmlAddTask(const QString& sprintName, const QString& storyName, const QString& taskName)
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
                QDomElement domElement = storyElements.at(i).toElement();
                QDomAttr attrStoryName = domElement.attributeNode(ATTRIBUTE_NAME);
                if (attrStoryName.value() == storyName)
                {
                    QDomElement tasks = domElement.firstChildElement(TASKS_TAG);
                    QDomElement newTask = document.createElement(TASK_TAG);
                    newTask.setAttribute(ATTRIBUTE_NAME, taskName);
                    tasks.appendChild(newTask);
                    break;
                }
            }
        }
    }

    _xmlSaveToFile();
}

void xmlSerializer::_xmlSaveToFile()
{
    mFile.open(QIODevice::WriteOnly);
    QTextStream stream(&mFile);
    stream << document.toString();
    mFile.close();
}

void xmlSerializer::xmlReadFile(SprintModel* sprintModel)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName(SPRINT_TAG);

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrSprintName = domElement.attributeNode(ATTRIBUTE_NAME);

        Sprint* newSprint = new Sprint(attrSprintName.value());
        sprintModel->append(newSprint);

        QDomNodeList storyElements = domElement.elementsByTagName(STORY_TAG);
        for (int j = 0; j < storyElements.size(); ++j)
        {
            QDomElement storyElement = storyElements.at(j).toElement();
            QDomAttr attrStoryName = storyElement.attributeNode(ATTRIBUTE_NAME);

            Story* newStory = new Story(attrStoryName.value(), newSprint);
            newSprint->storyModel()->append(newStory);

            QDomNodeList taskElements = storyElement.elementsByTagName(TASK_TAG);
            for (int k = 0; k < taskElements.size(); ++k)
            {
                QDomElement taskElement = taskElements.at(k).toElement();
                QDomAttr attrTaskName = taskElement.attributeNode(ATTRIBUTE_NAME);

                Task* newTask = new Task(attrTaskName.value(), newStory);
                newStory->taskModel()->append(newTask);
            }
        }
    }
}

