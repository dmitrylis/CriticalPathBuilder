#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

#include <functional>

#include "CpbSprintModel.h"

namespace CPB {

class XmlSerializer: public QObject
{
    Q_OBJECT

public:
    XmlSerializer(QObject* parent = nullptr);
    ~XmlSerializer();

    void readFile(SprintModel* sprintModel) const;

public slots:
    void createSprint(Sprint* sprint);
    void removeSprint(const QString& sprintTitle);
    void createStory(const QString& sprintTitle, Story* story);
    void updateStoryRow(const QString& sprintTitle, Story* story);
    void removeStory(const QString& sprintTitle, const QString& storyTitle);
    void createTask(const QString& sprintTitle, const QString& storyTitle, Task* task);
    void moveTask(const QString& sprintTitle, const QString& storyTitle, Task* task);
    void removeTask(const QString& sprintTitle, const QString& storyTitle, const QString& taskTitle);
    void updateDaysCount(const QString& sprintTitle, const QString& storyTitle, Task* task);

signals:
    void modelLoaded() const;

private:
    QDomElement cpbRootElement() const;

    void processNodeList(const QDomElement& parentElement,
                         const QString& tag,
                         const std::function<bool (QDomElement element)>& processFunction) const;

    void writeFile();

private:
    QFile m_file;
    QDomDocument m_document;
};

}
#endif // XMLSERIALIZER_H
