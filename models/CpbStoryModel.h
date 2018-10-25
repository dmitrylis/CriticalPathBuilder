#ifndef CPBSTORYMODEL_H
#define CPBSTORYMODEL_H

#include <QAbstractListModel>

#include "entities/CpbStory.h"

namespace CPB {

class StoryModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum StoryRoles {
        TitleRole = Qt::UserRole + 1,
        RowRole,
        TaskModelRole
    };
    Q_ENUM(StoryRoles)

    explicit StoryModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Story*> mStoryList;
};

}

#endif // CPBSTORYMODEL_H
