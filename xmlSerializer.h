#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>

class xmlSerializer
{
public:
    static xmlSerializer& Instance();
    xmlSerializer();
    void xmlCreate();
    void xmlAddSprint(QString sprint_name);
    void xmlAddStory(QString sprint_name, QString story_name);
    void xmlAddTask(QString sprint_name, QString story_name, QString task_name);

private:
    QFile mFile;
    QDomDocument document;
    xmlSerializer(xmlSerializer const&);
    xmlSerializer& operator= (xmlSerializer const &);
    void _xmlSaveToFile();
};

#endif // XMLSERIALIZER_H
