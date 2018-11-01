#ifndef SPRINTMODEL_H
#define SPRINTMODEL_H

#include <QAbstractListModel>

#include "entities/CpbSprint.h"

namespace CPB {

class SprintModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SprintRoles {
        SprintRole = Qt::UserRole + 1,
        TitleRole,
        StartDateRole,
        EndDateRole,
        StoryModelRole
    };
    Q_ENUM(SprintRoles)

    explicit SprintModel(QObject *parent = nullptr);

    // overrides
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // custom
    bool append(Sprint *sprint);
    bool remove(Sprint *sprint);
    bool appendStory(Sprint *sprint, Story *story);
    Sprint *getPrevious(Sprint *sprint) const;
    Sprint *getNext(Sprint *sprint) const;

protected:
    bool isValidIndex(int index) const;

private:
    QList<Sprint*> mSprintList;
};

}

#endif // SPRINTMODEL_H
