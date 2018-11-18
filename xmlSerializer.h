#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

class xmlSerializer
{
public:
    xmlSerializer();
    void xmlCreate();
    void xmlAddSprint(QString sprint_name);
    void xmlAddStory(QString sprint_name, QString story_name);
    void xmlAddTask(QString sprint_name, QString story_name, QString task_name);
    void xmlSaveCurrent();

private:
    QFile file;
    QDomDocument document;
};

#endif // XMLSERIALIZER_H
