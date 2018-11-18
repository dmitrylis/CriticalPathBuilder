#include "xmlSerializer.h"

xmlSerializer::xmlSerializer()
{
}

void xmlSerializer::xmlCreate()
{
    QFile file("mydoc.xml");

    file.open(QIODevice::ReadOnly);
    QDomDocument document;
    document.setContent(&file);
    file.close();

    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprints");

    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
}

void xmlSerializer::xmlAddSprint(QString sprint_name)
{
    QFile file("mydoc.xml");
    file.open(QIODevice::ReadOnly);
    document.setContent(&file);
    file.close();

    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprints");

    QDomElement new_sprint = document.createElement("Sprint");
    new_sprint.setAttribute("name", sprint_name);
    QDomElement story_elements = document.createElement("Stories");
    docEle.appendChild(new_sprint);
    new_sprint.appendChild(story_elements);

    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
}

void xmlSerializer::xmlAddStory(QString sprint_name, QString story_name)
{
    QFile file("mydoc.xml");
    file.open(QIODevice::ReadOnly);
    document.setContent(&file);
    file.close();

    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprint");

    for (int i = 0; i < elements.size(); ++i)
    {
        QDomElement domElement = elements.at(i).toElement();
        QDomAttr attr = domElement.attributeNode("name");
        if (attr.value() == sprint_name)
        {
            QDomNodeList stories = domElement.elementsByTagName("Stories");
            QDomElement new_story = document.createElement("Story");
            new_story.setAttribute("name", story_name);
            QDomElement tasks_elements = document.createElement("Tasks");
            domElement.appendChild(new_story);
            new_story.appendChild(tasks_elements);
            break;
        }
    }

    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
}

void xmlSerializer::xmlAddTask(QString sprint_name, QString story_name, QString task_name)
{
    QFile file("mydoc.xml");
    file.open(QIODevice::ReadOnly);
    document.setContent(&file);
    file.close();

    QDomElement docEle = document.documentElement();
    QDomNodeList elements = docEle.elementsByTagName("Sprint");

    QDomElement current_sprint;

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
                    QDomNodeList tasks = domElement.elementsByTagName("Tasks");
                    QDomElement new_task = document.createElement("Task");
                    new_task.setAttribute("name", task_name);
                    domElement.appendChild(new_task);
                    break;
                }
            }
        }
    }

    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
}

void xmlSerializer::xmlSaveCurrent()
{
    QFile file("mydoc.xml");

    file.open(QIODevice::WriteOnly);

    file.close();
}
