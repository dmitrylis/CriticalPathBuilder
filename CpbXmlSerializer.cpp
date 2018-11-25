#include "CpbXmlSerializer.h"

using namespace CPB;

namespace {
const QString TAG_CPB ("CPB");
const QString TAG_SPRINT ("Sprint");
const QString TAG_STORY ("Story");
const QString TAG_TASK ("Task");

const QString ATTRIBUTE_TITLE ("title");
const QString ATTRIBUTE_ROW_COUNT ("row_count");
const QString ATTRIBUTE_ROW ("row");
const QString ATTRIBUTE_COLUMN ("column");
const QString ATTRIBUTE_START_DATE ("start_date");
const QString ATTRIBUTE_END_DATE ("end_date");

const QString DATE_FORMAT ("dd.MM.yyyy");
}

XmlSerializer::XmlSerializer(QObject* parent) : QObject(parent)
{
    m_file.setFileName("struct.xml");
    m_file.open(QIODevice::ReadOnly);
    if (!m_document.setContent(&m_file))
    {
        m_file.close();
        QDomElement docEle = m_document.createElement(TAG_CPB);
        m_document.appendChild(docEle);
        writeFile();
    }
    m_file.close();
}

XmlSerializer::~XmlSerializer()
{
}

void XmlSerializer::readFile(SprintModel* sprintModel)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, &sprintModel] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        QDomAttr sprintStartDateAttr = sprintElement.attributeNode(ATTRIBUTE_START_DATE);
        QDomAttr sprintEndDateAttr = sprintElement.attributeNode(ATTRIBUTE_END_DATE);

        Sprint* newSprint = new Sprint(sprintTitleAttr.value(),
                                       QDate::fromString(sprintStartDateAttr.value(), DATE_FORMAT),
                                       QDate::fromString(sprintEndDateAttr.value(), DATE_FORMAT));
        sprintModel->append(newSprint);

        processNodeList(sprintElement, TAG_STORY, [this, &newSprint] (QDomElement storyElement) {
            QDomAttr storyTitleAttr = storyElement.attributeNode(ATTRIBUTE_TITLE);
            QDomAttr storyRowCountAttr = storyElement.attributeNode(ATTRIBUTE_ROW_COUNT);

            Story* newStory = new Story(storyTitleAttr.value(), newSprint);
            newStory->setRowCount(storyRowCountAttr.value().toInt());
            newSprint->storyModel()->append(newStory);

            processNodeList(storyElement, TAG_TASK, [&newStory] (QDomElement taskElement) {
                QDomAttr taskTitleAttr = taskElement.attributeNode(ATTRIBUTE_TITLE);
                QDomAttr taskRowAttr = taskElement.attributeNode(ATTRIBUTE_ROW);
                QDomAttr taskColumnAttr = taskElement.attributeNode(ATTRIBUTE_COLUMN);

                Task* newTask = new Task(taskTitleAttr.value(), taskRowAttr.value().toInt(), taskColumnAttr.value().toInt(), newStory);
                newStory->taskModel()->append(newTask);

                return false; // no break
            });

            return false; // no break
        });

        return false; // no break
    });

    emit modelLoaded();
}

void XmlSerializer::createSprint(Sprint* sprint)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    QDomElement newSprintElement = m_document.createElement(TAG_SPRINT);
    newSprintElement.setAttribute(ATTRIBUTE_TITLE, sprint->title());
    newSprintElement.setAttribute(ATTRIBUTE_START_DATE, sprint->startDate().toString(DATE_FORMAT));
    newSprintElement.setAttribute(ATTRIBUTE_END_DATE, sprint->endDate().toString(DATE_FORMAT));

    rootElement.appendChild(newSprintElement);

    writeFile();
}

void XmlSerializer::removeSprint(const QString& sprintTitle)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [sprintTitle] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            sprintElement.parentNode().removeChild(sprintElement);
            return true;
        }
        return false;
    });

    writeFile();
}

void XmlSerializer::createStory(const QString& sprintTitle, Story* story)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, sprintTitle, &story] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            QDomElement newStoryElement = m_document.createElement(TAG_STORY);
            newStoryElement.setAttribute(ATTRIBUTE_TITLE, story->title());
            newStoryElement.setAttribute(ATTRIBUTE_ROW_COUNT, story->rowCount());

            sprintElement.appendChild(newStoryElement);

            return true; // break from processing
        }

        return false; // no break
    });

    writeFile();
}

void XmlSerializer::removeStory(const QString& sprintTitle, const QString& storyTitle)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, sprintTitle, storyTitle] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            processNodeList(sprintElement, TAG_STORY, [storyTitle] (QDomElement storyElement) {
                QDomAttr storyTitleAttr = storyElement.attributeNode(ATTRIBUTE_TITLE);
                if (storyTitleAttr.value() == storyTitle)
                {
                    storyElement.parentNode().removeChild(storyElement);
                    return true;
                }

                return false; // no break
            });
        }

        return false; // no break
    });

    writeFile();
}

void XmlSerializer::updateStoryRow(const QString& sprintTitle, Story* story)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, sprintTitle, &story] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            processNodeList(sprintElement, TAG_STORY, [&story] (QDomElement storyElement) {
                QDomAttr storyTitleAttr = storyElement.attributeNode(ATTRIBUTE_TITLE);
                if (storyTitleAttr.value() == story->title())
                {
                    storyElement.setAttribute(ATTRIBUTE_ROW_COUNT, story->rowCount());

                    return true; // break from processing
                }

                return false; // no break
            });
        }

        return false; // no break
    });

    writeFile();
}

void XmlSerializer::createTask(const QString& sprintTitle, const QString& storyTitle, Task* task)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, sprintTitle, storyTitle, &task] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            processNodeList(sprintElement, TAG_STORY, [this, storyTitle, &task] (QDomElement storyElement) {
                QDomAttr storyTitleAttr = storyElement.attributeNode(ATTRIBUTE_TITLE);
                if (storyTitleAttr.value() == storyTitle)
                {
                    QDomElement newTaskElement = m_document.createElement(TAG_TASK);
                    newTaskElement.setAttribute(ATTRIBUTE_TITLE, task->title());
                    newTaskElement.setAttribute(ATTRIBUTE_ROW, task->row());
                    newTaskElement.setAttribute(ATTRIBUTE_COLUMN, task->column());

                    storyElement.appendChild(newTaskElement);

                    return true; // break from processing
                }

                return false; // no break
            });
        }

        return false; // no break
    });

    writeFile();
}

void XmlSerializer::moveTask(const QString& sprintTitle, const QString& storyTitle, Task* task)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, sprintTitle, storyTitle, task] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            processNodeList(sprintElement, TAG_STORY, [this, storyTitle, task] (QDomElement storyElement) {
                QDomAttr storyTitleAttr = storyElement.attributeNode(ATTRIBUTE_TITLE);
                if (storyTitleAttr.value() == storyTitle)
                {
                    processNodeList(storyElement, TAG_TASK, [task] (QDomElement taskElement)
                    {
                        QDomAttr taskTitleAttr = taskElement.attributeNode(ATTRIBUTE_TITLE);
                        if (taskTitleAttr.value() == task->title())
                        {
                            taskElement.setAttribute(ATTRIBUTE_ROW, task->row());
                            taskElement.setAttribute(ATTRIBUTE_COLUMN, task->column());

                            return true;
                        }

                        return false; // break from processing
                    });
                }

                return false; // no break
            });
        }

        return false; // no break
    });

    writeFile();
}

void XmlSerializer::removeTask(const QString& sprintTitle, const QString& storyTitle, const QString& taskTitle)
{
    QDomElement rootElement = cpbRootElement();
    if (rootElement.isNull())
    {
        return;
    }

    processNodeList(rootElement, TAG_SPRINT, [this, sprintTitle, storyTitle, taskTitle] (QDomElement sprintElement) {
        QDomAttr sprintTitleAttr = sprintElement.attributeNode(ATTRIBUTE_TITLE);
        if (sprintTitleAttr.value() == sprintTitle)
        {
            processNodeList(sprintElement, TAG_STORY, [this, storyTitle, taskTitle] (QDomElement storyElement) {
                QDomAttr storyTitleAttr = storyElement.attributeNode(ATTRIBUTE_TITLE);
                if (storyTitleAttr.value() == storyTitle)
                {
                    processNodeList(storyElement, TAG_TASK, [taskTitle] (QDomElement taskElement)
                    {
                        QDomAttr taskTitleAttr = taskElement.attributeNode(ATTRIBUTE_TITLE);
                        if (taskTitleAttr.value() == taskTitle)
                        {
                            taskElement.parentNode().removeChild(taskElement);
                            return true;
                        }

                        return false; // break from processing
                    });
                }

                return false; // no break
            });
        }

        return false; // no break
    });

    writeFile();
}

QDomElement XmlSerializer::cpbRootElement() const
{
    QDomElement rootElement = m_document.documentElement();

    if (rootElement.tagName() != TAG_CPB)
    {
        qWarning("File format is not applicable for CPB");
        return QDomElement();
    }

    return rootElement;
}

void XmlSerializer::processNodeList(const QDomElement& parentElement,
                                    const QString& tag,
                                    const std::function<bool (QDomElement element)>& processFunction)
{
    QDomNodeList nodeList = parentElement.elementsByTagName(tag);
    for (int i = 0; i < nodeList.size(); ++i)
    {
        if (processFunction(nodeList.at(i).toElement()))
        {
            break;
        }
    }
}

void XmlSerializer::writeFile()
{
    m_file.open(QIODevice::WriteOnly);
    QTextStream stream(&m_file);
    stream << m_document.toString();
    m_file.close();
}
