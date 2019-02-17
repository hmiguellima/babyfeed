#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>
#include <QStringList>
#include <QSet>
#include <QIcon>

#ifdef Q_OS_SYMBIAN
    #include "contacts/xqcontacts.h"
#endif

class ContactsModel : public QAbstractListModel
{
public:
    Q_OBJECT

private:
#ifdef Q_OS_SYMBIAN
    static XQContacts contacts;
#endif
    QStringList namesList;
    QIcon *transparentIcon;
    QIcon *notfIcon;

signals:
    void eventsChanged();

public:
    ContactsModel(QSet<QString> notified);
    ~ContactsModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    long getContactIdFromRow(int row) const;
    QString getContactKeyFromRow(int row) const;
    static QString getContactPhone(QString contactKey);

public slots:
    void setNotification(int row, bool notified);
};

#endif // CONTACTSMODEL_H
