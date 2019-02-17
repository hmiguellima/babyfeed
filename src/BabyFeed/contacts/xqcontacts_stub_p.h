#ifndef XQCONTACTS_STUB_P_H_
#define XQCONTACTS_STUB_P_H_

// INCLUDES
#include <QObject>
#include <QString>
#include "xqcontacts.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
class XQContactsPrivate : public QObject
{
    Q_OBJECT

public:
    XQContactsPrivate();
    ~XQContactsPrivate();
    
    int count() const;
    XQContact contactById(long int contactId) const;
    QList<long int> findContactIds(QString value, XQContactField::ContactFieldType type) const;
    QList<XQContact> findContacts(QString value, XQContactField::ContactFieldType type) const;
    QString contactNameById(long int contactId) const;
    long int addContact(const XQContact& contact);
    bool updateContact(const XQContact& contact);
    bool removeContact(long int contactId);
    int importvCard(const QString& fileName);
    bool exportAsvCard(const QString& fileName, long int contactId) const;
    bool updateContactFields(long int contactId, const QList<XQContactField>& fields);
public: // Data
    XQContacts::Error error;	
    QList<long int> iContactIds;

private: // Data
};

#endif // XQCONTACTS_STUB_P_H_

// End of file
