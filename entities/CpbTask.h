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

public:
    explicit Task(Story* parentStory, const QString& title, const QString& owner, int row, int column);
    ~Task();

    Story* parentStory() const;
    QString title() const;
    QString owner() const;
    int row() const;
    int column() const;
    int daysCount() const;

    void setOwner(const QString& owner);
    void setRow(int row);
    void setColumn(int column);
    void setDaysCount(int daysCount);

private:
    Story* m_parentStory;
    QString m_title;
    QString m_owner;
    int m_row;
    int m_column;
    int m_daysCount;
};

}

#endif // CPBTASK_H
