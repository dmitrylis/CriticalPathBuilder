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
    explicit XmlSerializer(QObject* parent = nullptr);
    ~XmlSerializer();

    void readFile(SprintModel* sprintModel) const;

public slots:
    void createSprint(Sprint* sprint);
    void removeSprint(const QString& sprintTitle);

    void createStory(const QString& sprintTitle, Story* story);
    void removeStory(const QString& sprintTitle, const QString& storyTitle);
    void updateStoryRow(const QString& sprintTitle, Story* story);

    void createTask(const QString& sprintTitle, const QString& storyTitle, Task* task);
    void removeTask(const QString& sprintTitle, const QString& storyTitle, const QString& taskTitle);
    void updateTaskPosition(const QString& sprintTitle, const QString& storyTitle, Task* task);
    void updateTaskDaysCount(const QString& sprintTitle, const QString& storyTitle, Task* task);

signals:
    void modelLoaded() const;

private:
    QDomElement cpbRootElement() const;

    void processNodeList(const QDomElement& parentElement,
                         const QString& tag,
                         const std::function<bool (QDomElement element)>& processFunction) const;

    void updateStory(const QString& sprintTitle,
                     const QString& storyTitle,
                     const std::function<void (QDomElement element)>& updateFunction);

    void updateTask(const QString& sprintTitle,
                    const QString& storyTitle,
                    const QString& taskTitle,
                    const std::function<void (QDomElement element)>& updateFunction);

    void writeFile();

private:
    QFile m_file;
    QDomDocument m_document;
};

}
#endif // XMLSERIALIZER_H
