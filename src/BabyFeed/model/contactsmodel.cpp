#include "contactsmodel.h"
#include <QString>
#include <QVariant>
#include "global.h"
#include <QList>
#include <QHash>
#include <QDebug>
#include <QContactId>
#include <QContact>
#include <QContactPhoneNumber>
#include <QContactDetail>
#include <QContactDetailDefinition>
#include <QContactFetchHint>
#include <QtCore>

class ContactsLoader: public QThread
{
public:
    void fetchContacts(ContactsModel *model, QSet<QString> notified) {
        this->notified=notified;
        this->model=model;
        start();
    }

    void run() {
        QContactManager manager;
        QStringList namesList;
        QContactLocalId contactId;
        QString contactName;
        QString contactKey;
        QList<QContact> contactList;
        QContact contact;

        #ifdef Q_OS_SYMBIAN
            RThread().SetPriority(EPriorityMuchLess);
        #endif

        namesList.clear();
        contactList=manager.contacts();

        foreach (contact, contactList)
        {
            contactName=contact.displayLabel();

            if (contactName.trimmed().length()==0)
                continue;

            contactId=contact.localId();
            contactKey=QString("%0|%1").arg(contactName).arg(contactId);

            if (notified.contains(contactKey))
                namesList.append(QString("%0|%1").arg("a").arg(contactKey));
            else
                namesList.append(QString("%0|%1").arg("b").arg(contactKey));
        }

        if (namesList.length()==0)
            namesList.append(QString("c|<No Contacts>|0"));

        namesList.sort();
        QMetaObject::invokeMethod(model, "loadModel", Q_ARG(QStringList, namesList));
    }

private:
    QSet<QString> notified;
    ContactsModel *model;
};


ContactsLoader contactsLoader;

ContactsModel::ContactsModel(QObject* parent) : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;

    roles[IconRole] = "icon";
    roles[ContactNameRole] = "contactName";
    roles[NotificationTypeIndexRole] = "notificationType";
    setRoleNames(roles);

    this->baby=&noBaby;
    transparentIcon=QString("qrc:/icons/icons/transparent.png");
    notfIcon=QString("qrc:/icons/icons/internet-mail.png");
}

ContactsModel::~ContactsModel()
{
}

void ContactsModel::setNotified(Baby* baby)
{
    this->baby=baby;
    namesList.clear();
    namesList.append(QString("c|<Loading contacts...>|0"));
    reset();
    if (!contactsLoader.isRunning())
        contactsLoader.wait();
    contactsLoader.fetchContacts(this, baby->getNotfContactKeys());
}


int ContactsModel::rowCount(const QModelIndex& parent) const
{
    int count=namesList.size();
    return count;
}

QVariant ContactsModel::data(const QModelIndex& index, int role) const
{
    QString contactData;

    if (!index.isValid())
        return QVariant();

    if (index.row() >= namesList.size())
        return QVariant();

    contactData=namesList[index.row()];

    switch (role)
    {
    case IconRole:
        if (contactData.toAscii().at(0)=='a')
            return notfIcon;
        else
            return transparentIcon;
    case ContactNameRole:
        return QVariant(contactData.split("|")[1]);
    case NotificationTypeIndexRole:
        if (contactData.toAscii().at(0)=='c')
            return "";
        else
            return QString(baby->getNotificationType(getContactKeyFromRow(index.row())));
    default:
        return QVariant();
    }
}

QVariant ContactsModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    return QVariant();
}

long ContactsModel::getContactIdFromRow(int row) const
{
    QString contactData=namesList.value(row);

    return (long)QVariant(contactData.split("|")[2]).toDouble();
}

QString ContactsModel::getContactKeyFromRow(int row) const
{
    QStringList contactData=namesList.value(row).split("|");

    return QString("%0|%1").arg(contactData[1]).arg(contactData[2]);
}

void ContactsModel::setNotification(int row, bool notified)
{
    QStringList contactData=namesList.value(row).split("|");
    QString notfInd;

    if (notified)
        notfInd="a";
    else
        notfInd="b";
    namesList[row]=QString("%0|%1|%2").arg(notfInd).arg(contactData[1]).arg(contactData[2]);
    namesList.sort();
    reset();
}

QString ContactsModel::getContactPhone(QString contactKey)
{
    long id=(long)QVariant(contactKey.split("|")[1]).toDouble();
    QContactPhoneNumber phn;
    QContact contact;
    QString phoneStr="";
    QMap<QString, QContactDetailDefinition> defs = manager.detailDefinitions(QContactType::TypeContact);

    contact=manager.contact(id);

    qDebug() << "ContactsModel::getContactPhone:contact.id().localId():" << contact.id().localId();

    if (defs.contains(QContactPhoneNumber::DefinitionName))
    {
        phn=contact.detail(QContactPhoneNumber::DefinitionName);
        phoneStr=phn.value(QContactPhoneNumber::FieldNumber);
    }
    else
        phoneStr="99999999";

    qDebug() << "ContactsModel::getContactPhone:phone:" << phoneStr;

    return phoneStr;
}

void ContactsModel::loadModel(QStringList namesList)
{
    this->namesList=namesList;
    reset();
    emit contactsLoaded();
}
