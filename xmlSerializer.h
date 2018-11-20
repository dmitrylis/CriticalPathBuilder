#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include "CpbSprintModel.h"

class xmlSerializer: public QObject
{
    Q_OBJECT

public:
    xmlSerializer(QObject* parent = nullptr);
    void xmlAddSprint(QString sprint_name);
    void xmlAddStory(QString sprint_name, QString story_name);
    void xmlAddTask(QString sprint_name, QString story_name, QString task_name);
    void xmlReadFile(CPB::SprintModel* sprintModel);

private:
    QFile mFile;
    QDomDocument document;
    void _xmlSaveToFile();
};


#endif // XMLSERIALIZER_H
