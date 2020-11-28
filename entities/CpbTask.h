#ifndef CPBTASK_H
#define CPBTASK_H

#include <QObject>

namespace CPB {

class Story;

class Task : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Story* parentStory READ parentStory CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString owner READ owner CONSTANT)
    Q_PROPERTY(TaskType type READ type CONSTANT)

public:
    enum TaskType {
        DevelopmentTask = 0,
        QaTask,
        ResearchTask
    };
    Q_ENUM(TaskType)

public:
    explicit Task(Story* parentStory, const QString& title, const QString& owner, TaskType type, int row, int column, int daysCount = 1);
    ~Task();

    Story* parentStory() const;
    QString title() const;
    QString owner() const;
    TaskType type() const;
    int row() const;
    int column() const;
    int daysCount() const;

    void setOwner(const QString& owner);
    void setType(TaskType type);
    void setRow(int row);
    void setColumn(int column);
    void setDaysCount(int daysCount);

private:
    Story* m_parentStory;
    QString m_title;
    QString m_owner;
    TaskType m_type;
    int m_row;
    int m_column;
    int m_daysCount;
};

}

#endif // CPBTASK_H
