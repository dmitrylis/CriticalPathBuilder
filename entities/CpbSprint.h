#ifndef CPBSPRINT_H
#define CPBSPRINT_H

#include <QObject>

#include "CpbStoryModel.h"
#include "CpbDaysModel.h"

namespace CPB {

class Sprint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(StoryModel* storyModel READ storyModel CONSTANT)
    Q_PROPERTY(DaysModel* daysModel READ daysModel CONSTANT)

public:
    explicit Sprint(const QString& title, const QDate& startDate, int weeksCount, QObject *parent = nullptr);
    explicit Sprint(const QString& title, const QDate& startDate, const QDate& endDate, QObject *parent = nullptr);
    virtual ~Sprint();

    QString title() const;
    QDate startDate() const;
    QDate endDate() const;
    int daysCount() const;

    StoryModel* storyModel() const;
    DaysModel* daysModel() const;

private:
    QString m_title;
    QDate m_startDate;
    QDate m_endDate;
    int m_daysCount;

    StoryModel* m_storyModel;
    DaysModel* m_daysModel;
};

}

#endif // CPBSPRINT_H
