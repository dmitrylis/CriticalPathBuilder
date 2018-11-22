#ifndef CPBTASK_H
#define CPBTASK_H

#include <QObject>

namespace CPB {

class Story;

class Task : public QObject
{
    Q_OBJECT

public:
    explicit Task(const QString& title, int row, int column, Story* parentStory);
    virtual ~Task();

    Story* parentStory() const;
    QString title() const;
    int row() const;
    int column() const;

    int setRow(int row);
    int setColumn(int column);

private:
    Story* m_parentStory;
    QString m_title;
    int m_row;
    int m_column;
};

}

#endif // CPBTASK_H
