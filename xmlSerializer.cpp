#include "xmlSerializer.h"

using namespace CPB;

xmlSerializer::xmlSerializer(QObject* parent) : QObject(parent)
{
    mFile.setFileName("mydoc.xml");

    mFile.open(QIODevice::ReadOnly);
    if (!document.setContent(&mFile))
    {
        mFile.close();
        QDomElement docEle = document.createElement("Sprints");
        document.appendChild(docEle);
        _xmlSaveToFile();
    }
    mFile.close();
}

void xmlSerializer::xmlAddSprint(QString sprintName)
{
    QDomElement docElement = document.documentElement();
    QDomNodeList sprintsElements = docElement.elementsByTagName("Sprints");
    QDomElement newSprint = document.createElement("Sprint");
    newSprint.setAttribute("name", sprintName);
    QDomElement storyElements = document.createElement("Stories");

    docElement.appendChild(newSprint);
    newSprint.appendChild(storyElements);

    _xmlSaveToFile();
}

void xmlSerializer::xmlAddStory(QString sprintName, QString storyName)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrName = domElement.attributeNode("name");
        if (attrName.value() == sprintName)
        {
            QDomElement stories = domElement.firstChildElement("Stories");
            QDomElement newStory = document.createElement("Story");
            newStory.setAttribute("name", storyName);
            QDomElement tasksElements = document.createElement("Tasks");
            stories.appendChild(newStory);
            newStory.appendChild(tasksElements);
            break;
        }
    }

    _xmlSaveToFile();
}

void xmlSerializer::xmlAddTask(QString sprintName, QString storyName, QString taskName)
{
    QDomElement docElements = document.documentElement();
    QDomNodeList elements = docElements.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrSprintName = domElement.attributeNode("name");
        if (attrSprintName.value() == sprintName)
        {
            QDomNodeList storyElements = domElement.elementsByTagName("Story");
            for (int i = 0; i < storyElements.size(); ++i)
            {
                QDomElement domElement = storyElements.at(i).toElement();
                QDomAttr attrStoryName = domElement.attributeNode("name");
                if (attrStoryName.value() == storyName)
                {
                    QDomElement tasks = domElement.firstChildElement("Tasks");
                    QDomElement newTask = document.createElement("Task");
                    newTask.setAttribute("name", taskName);
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
    QDomNodeList elements = docElements.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attrSprintName = domElement.attributeNode("name");

        Sprint* newSprint = new Sprint(attrSprintName.value());
        sprintModel->append(newSprint);

        QDomNodeList storyElements = domElement.elementsByTagName("Story");
        for (int j = 0; j < storyElements.size(); ++j)
        {
            QDomElement storyElement = storyElements.at(j).toElement();
            QDomAttr attrStoryName = storyElement.attributeNode("name");

            Story* newStory = new Story(attrStoryName.value(), newSprint);
            newSprint->storyModel()->append(newStory);

            QDomNodeList taskElements = storyElement.elementsByTagName("Task");
            for (int k = 0; k < taskElements.size(); ++k)
            {
                QDomElement taskElement = taskElements.at(k).toElement();
                QDomAttr attrTaskName = taskElement.attributeNode("name");

                Task* newTask = new Task(attrTaskName.value(), newStory);
                newStory->taskModel()->append(newTask);
            }
        }
    }
}

