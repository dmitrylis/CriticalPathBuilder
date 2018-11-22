#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include "CpbSprintModel.h"

namespace CPB {

class XmlSerializer: public QObject
{
    Q_OBJECT

    //methods
public:
    XmlSerializer(QObject* parent = nullptr);
    void xmlAddSprint(Sprint* sprint);
    void xmlAddStory(const QString& sprintName, Story* story);
    void xmlChangeStoryRow(const QString& sprintName, Story* story);
    void xmlAddTask(const QString& sprintName, const QString& storyName, Task* task);
    void xmlReadFile(SprintModel* sprintModel);

private:
    void _xmlSaveToFile();

    //variables
private:
    QFile mFile;
    QDomDocument document;
};

}
#endif // XMLSERIALIZER_H
