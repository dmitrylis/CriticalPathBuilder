#include "xmlSerializer.h"

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

void xmlSerializer::xmlAddSprint(QString sprint_name)
{
    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprints");

    QDomElement new_sprint = document.createElement("Sprint");
    new_sprint.setAttribute("name", sprint_name);
    QDomElement story_elements = document.createElement("Stories");
    docEle.appendChild(new_sprint);
    new_sprint.appendChild(story_elements);

    _xmlSaveToFile();
}

void xmlSerializer::xmlAddStory(QString sprint_name, QString story_name)
{
    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attr = domElement.attributeNode("name");
        if (attr.value() == sprint_name)
        {
            QDomElement stories = domElement.firstChildElement("Stories");
            QDomElement new_story = document.createElement("Story");
            new_story.setAttribute("name", story_name);
            QDomElement tasks_elements = document.createElement("Tasks");
            stories.appendChild(new_story);
            new_story.appendChild(tasks_elements);
            break;
        }
    }

    _xmlSaveToFile();
}

void xmlSerializer::xmlAddTask(QString sprint_name, QString story_name, QString task_name)
{
    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attr = domElement.attributeNode("name");
        if (attr.value() == sprint_name)
        {
            QDomNodeList story_elements = domElement.elementsByTagName("Story");
            for (int i = 0; i < story_elements.size(); ++i)
            {
                QDomElement domElement = story_elements.at(i).toElement();
                QDomAttr attr = domElement.attributeNode("name");
                if (attr.value() == story_name)
                {
                    QDomElement tasks = domElement.firstChildElement("Tasks");
                    QDomElement new_task = document.createElement("Task");
                    new_task.setAttribute("name", task_name);
                    tasks.appendChild(new_task);
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

void xmlSerializer::xmlReadFile()
{
    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attr = domElement.attributeNode("name");

    }
}

