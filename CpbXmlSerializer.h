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
    virtual ~XmlSerializer();

    void readFile(SprintModel* sprintModel);

public slots:
    void createSprint(Sprint* sprint);
    void createStory(const QString& sprintTitle, Story* story);
    void updateStoryRow(const QString& sprintTitle, Story* story);
    void createTask(const QString& sprintTitle, const QString& storyTitle, Task* task);

signals:
    void modelLoaded() const;

private:
    QDomElement cpbRootElement() const;

    void processNodeList(const QDomElement& parentElement,
                         const QString& tag,
                         const std::function<bool (QDomElement element)>& processFunction);

    void writeFile();

private:
    QFile m_file;
    QDomDocument m_document;
};

}
#endif // XMLSERIALIZER_H
