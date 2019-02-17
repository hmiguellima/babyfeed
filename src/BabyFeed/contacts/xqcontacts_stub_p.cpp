// INCLUDE FILES
#include "xqcontacts_stub_p.h"

XQContactsPrivate::XQContactsPrivate()
{
}

XQContactsPrivate::~XQContactsPrivate()
{
}

int XQContactsPrivate::count() const
{
    return 0;
}

XQContact XQContactsPrivate::contactById(long int contactId) const
{
}

QList<long int> XQContactsPrivate::findContactIds(QString value, XQContactField::ContactFieldType type) const
{
}

QList<XQContact> XQContactsPrivate::findContacts(QString value, XQContactField::ContactFieldType type) const
{
}

QString XQContactsPrivate::contactNameById(long int contactId) const
{
}

long int XQContactsPrivate::addContact(const XQContact& contact)
{
}

bool XQContactsPrivate::updateContact(const XQContact& contact)
{
}

bool XQContactsPrivate::removeContact(long int contactId)
{
}


bool XQContactsPrivate::updateContactFields(long int contactId, const QList<XQContactField>& fields)
{

}

// End of file
