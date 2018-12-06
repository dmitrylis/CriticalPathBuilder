#ifndef CPBPOPUPMANAGER_H
#define CPBPOPUPMANAGER_H

#include <QObject>
#include <QString>
#include <QVariant>

namespace CPB {

class PopupManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString popupPath READ popupPath NOTIFY popupChanged)
    Q_PROPERTY(QVariantList popupData READ popupData NOTIFY popupChanged)

public:
    explicit PopupManager(QObject *parent = nullptr);
    ~PopupManager();

    QString popupPath() const;
    QVariantList popupData() const;

    Q_INVOKABLE void showPopup(const QString& popupPath, const QVariantList& popupData = QVariantList());
    Q_INVOKABLE void showCreateSprintPopup();
    Q_INVOKABLE void showCreateStoryPopup(const QVariant& parentSprint);
    Q_INVOKABLE void showCreateTaskPopup(int row, int column, const QVariant& parentStory);
    Q_INVOKABLE void showRemoveSprintPopup(const QVariant& sprintToRemove);
    Q_INVOKABLE void showRemoveStoryPopup(const QVariant& storyToRemove);
    Q_INVOKABLE void showRemoveTaskPopup(const QVariant& taskToRemove);
    Q_INVOKABLE void hidePopup();

signals:
    void popupChanged();

private:
    QString m_popupPath;
    QVariantList m_popupData;
};

}

#endif // CPBPOPUPMANAGER_H
