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

    //methods
public:
    xmlSerializer(QObject* parent = nullptr);
    void xmlAddSprint(const QString& sprintName);
    void xmlAddStory(const QString& sprintName, const QString& storyName);
    void xmlAddTask(const QString& sprintName, const QString& storyName, const QString& taskName);
    void xmlReadFile(CPB::SprintModel* sprintModel);

private:
    void _xmlSaveToFile();

    //variables
private:
    QFile mFile;
    QDomDocument document;
};


#endif // XMLSERIALIZER_H
