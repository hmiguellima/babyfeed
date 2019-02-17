#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>
#include <QStringList>
#include <QSet>
#include <QIcon>
#include "baby.h"
#include "nobaby.h"
#include <QContactManager>

using namespace QtMobility;

class ContactsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RecordRoles {
        IconRole = Qt::UserRole + 1,
        ContactNameRole,
        NotificationTypeIndexRole
    };

    ContactsModel(QObject* parent);

    ~ContactsModel();

    void setNotified(Baby* baby);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    long getContactIdFromRow(int row) const;
    QString getContactKeyFromRow(int row) const;
    QString getContactPhone(QString contactKey);

signals:
    void eventsChanged();
    void contactsLoaded();

public slots:
    void setNotification(int row, bool notified);
    Q_INVOKABLE void loadModel(QStringList namesList);

private:
    QContactManager manager;
    QStringList namesList;
    QString transparentIcon;
    QString notfIcon;
    Baby* baby;
    NoBaby noBaby;
};

#endif // CONTACTSMODEL_H
