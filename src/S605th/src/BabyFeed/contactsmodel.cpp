#include "contactsmodel.h"
#include <QMessageBox>
#include <QString>
#include <QVariant>

#ifdef Q_OS_SYMBIAN
    XQContacts ContactsModel::contacts;
#endif

ContactsModel::ContactsModel(QSet<QString> notified) : QAbstractListModel(0)
{
    long contactId;
    QString contactName;
    QString contactKey;

    transparentIcon=new QIcon(QString::fromUtf8(":/icons/icons/transparent.png"));
    notfIcon=new QIcon(QString::fromUtf8(":/icons/icons/internet-mail.png"));
#ifdef Q_OS_SYMBIAN
    foreach (contactId,contacts.contactIds())
    {
        contactName=contacts.contactNameById(contactId);
        contactKey=QString("%0|%1").arg(contactName).arg(contactId);

        //QMessageBox::information(0, "teste", notified.values()[0]+";"+contactKey);

        if (notified.contains(contactKey))
            namesList.append(QString("%0|%1").arg("a").arg(contactKey));
        else
            namesList.append(QString("%0|%1").arg("b").arg(contactKey));
    }
#else
    namesList.append("b|hugo|1");
#endif
    namesList.sort();
}

ContactsModel::~ContactsModel()
{
    delete transparentIcon;
    delete notfIcon;
}


int ContactsModel::rowCount(const QModelIndex& parent) const
{
    return namesList.size();
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
    case Qt::DecorationRole:
        if (contactData.toAscii().at(0)=='a')
            return *notfIcon;
        else
            return *transparentIcon;
    case Qt::DisplayRole:
        return QVariant(contactData.split("|")[1]);
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
#ifdef Q_OS_SYMBIAN
    long id=(long)QVariant(contactKey.split("|")[1]).toDouble();
    return contacts.contactById(id).fieldByType(XQContactField::ContactFieldTypePhoneNumber).value().toString();
#else
    return "";
#endif
}
