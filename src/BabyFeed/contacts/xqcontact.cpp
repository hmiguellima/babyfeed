// INCLUDE FILES
#include <QImage>
#include <QByteArray>
#include "xqcontact.h"
#include "xqcontact_p.h"

/****************************************************
 *
 * XQContact
 *
 ****************************************************/
/*!
    \class XQContact

    \brief The XQContact class can be used for storing and handling contact fields.
    
*/

/*!
    Creates a contact.
*/
XQContact::XQContact()
    : isContactNull(true),
      contactId(0)
{
}

/*!
    Creates a copy of a given contact.

   \param other The contact to be copied.
*/
XQContact::XQContact(const XQContact& other)
{
    contactFields.clear();
    if (other.isNull())
    {
        isContactNull = true;
        contactId = 0;
    }
    else
    {
        isContactNull = false;
        contactId = other.id();
        const QList<XQContactField> fields = other.fields();
        for (int i = 0; i < fields.count(); i++ )
        {
            contactFields.append(fields.at(i));
        }
    }
}


/*!
    Destroys the contact.
*/
XQContact::~XQContact()
{
}

/*!
    \enum XQContactField::ContactFieldType

    This enum defines all the possible field types for a XQContactField object.
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeAddress
    Street Address (vCard: the street address of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypePostOffice
    P.O Box (vCard: the post office box of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeExtendedAddress
    Extended Address (vCard: the extended address of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeLocality
    City (vCard: the locality (e.g., city) of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeRegion
    State (vCard: the region (e.g., state or province) of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypePostCode
    Postal code (vCard: the postal code of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeCountry
    Country (vCard: the country name of 'ADR' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeCompanyName
    Company name (vCard: 'ORG' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypePhoneNumber
    Phone number (vCard: 'TEL' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeGivenName
    Given name (vCard: Given Name of 'N' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeFamilyName
    Family name (vCard: the Family Name of 'N' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeAdditionalName
    Additional name (e.g., Middle name) (vCard: Additional Names of 'N' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeSuffixName
    Suffix name (vCard: Honorific Suffixes of 'N' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypePrefixName
    Prefix name (vCard: Honorific Prefixes of 'N' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeEMail
    Email (vCard: 'EMAIL' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeNote
    Note (vCard: 'NOTE' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeBirthday
    Date of Birthday (vCard: 'BDAY' type), should contain QDateTime as a value.
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeUrl
    URL (vCard: 'URL' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypePicture
    Picture (vCard: 'PHOTO' type), should contain QImage or QString holding a
    file path to picture.
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeJobTitle
    Job title (vCard: 'TITLE' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeSecondName
    Second name (e.g., Nick name) (vCard: 'NICKNAME' type)
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeSIPID
    SIP ID
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeAssistant
    Assistant
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeAnniversary
    Anniversary, should contain QDateTime as a value.
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeSpouse
    Spouse name
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeChildren
    Names of the contact's children
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeDepartmentName
    Department name
*/
/*! \var XQContactField::ContactFieldType XQContactField::ContactFieldTypeUnknown
    Field type is unknown
*/

/*!
    Adds a new field to the contact.

    \param field The field to be added to the contact
    \sa removeField(), fields()
*/
void XQContact::addField(XQContactField field)
{
    if (isContactNull)
    {
        isContactNull = false;
    }
    contactFields.append(field);
}

/*!
    Removes a field from the contact. The field is identified using
    field id.

    \param field The field to be removed
    \sa addField(), fields()
*/
bool XQContact::removeField(XQContactField field)
{
    if (isContactNull)
    {
        return false;
    }
    for (int i=0; i < contactFields.count(); i++ )
    {
        if (contactFields[i].id() == field.id())
        {
            contactFields.removeAt(i);
            return true;
        }
    }
    return false;
}

/*!
    Removes the given type of field from the contact.

    \param fieldType The type of the field to be removed
    \sa addField(), fields()
*/
bool XQContact::removeFieldByType(XQContactField::ContactFieldType fieldType)
{
    if (isContactNull)
    {
        return false;
    }
    for (int i=0; i < contactFields.count(); i++ )
    {
        if (contactFields[i].type() == fieldType)
        {
            contactFields.removeAt(i);
            return true;
        }
    }
    return false;
}

/*!
    Returns the first occurence of a field with the type \a fieldType that is contained in this contact.

    \param fieldType the type of the field to be returned
    \return the matching field on success; null field on failure
    \sa addField(), fields()
*/
XQContactField XQContact::fieldByType(XQContactField::ContactFieldType fieldType) const
{
    XQContactField field;
    if (isContactNull)
    {
        return field;
    }
    for (int i=0; i < contactFields.count(); i++ )
    {
        if (contactFields[i].type() == fieldType)
        {
            return contactFields[i];
        }
    }
    return field;
}

/*!
    Returns the list of fields in this contact that have the type \a fieldType.

    \param fieldType the type of the field to be returned
    \return The list of matching fields on success; null list on failure.
    \sa addField(), fields()
*/
QList<XQContactField> XQContact::fieldsByType(XQContactField::ContactFieldType fieldType) const
{
    QList<XQContactField> fields;
    if (isContactNull)
    {
        return fields;
    }
    for (int i=0; i < contactFields.count(); i++ )
    {
        if (contactFields[i].type() == fieldType)
        {
            fields.append(contactFields[i]);
        }
    }
    return fields;
}

/*!
    Returns the list of address fields in the contact.
    
    Fields having any of the following types are returned:
    ContactFieldTypeAddress, ContactFieldTypePostOffice,
    ContactFieldTypeExtendedAddress, ContactFieldTypeLocality,
    ContactFieldTypeRegion, ContactFieldTypePostCode, ContactFieldTypeCountry.

    \return The list of address fields on success; null list on failure
    \sa addField(), fields()
*/
QList<XQContactFieldAddress> XQContact::addressFields() const
{
    QList<XQContactFieldAddress> fields;
    if (isContactNull)
    {
        return fields;
    }
    XQContactField::ContactFieldType fieldType;
    for (int i=0; i < contactFields.count(); i++ )
    {
        fieldType = contactFields[i].type();
        if ((fieldType >= XQContactField::ContactFieldTypeAddress) &&
                (fieldType <= XQContactField::ContactFieldTypeCountry))
        {
            fields.append(contactFields[i].toFieldAddress());
        }
    }
    return fields;
}

/*!
    \return A list containing all the fields of the contact
*/
QList<XQContactField> XQContact::fields() const
{
    return contactFields;
}

/*!
    \return Id of this contact
*/
long int XQContact::id() const
{
    return contactId;
}

/*!
    \return True if the contact is empty; otherwise returns false.
*/
bool XQContact::isNull() const
{
    if (isContactNull)
    {
        return true;
    }
    return false;
}

/*!
    Assigns \a other to this contact and returns a reference
    to this contact.

    \param other The other contact
    \return A reference to this contact
*/
XQContact& XQContact::operator=(const XQContact& other)
{
    contactFields.clear();
    if (other.isNull())
    {
        isContactNull = true;
        contactId = 0;
    }
    else
    {
        contactId = other.id();
        isContactNull = false;
        const QList<XQContactField> fields = other.fields();
        for (int i = 0; i < fields.count(); i++ )
        {
            contactFields.append(fields.at(i));
        }
    }
    return *this;
}


/****************************************************
 *
 * XQContactField
 *
 ****************************************************/

 /// \cond IGNORE
XQContactFieldPrivate::XQContactFieldPrivate()
    : ref(1),
      type(XQContactField::ContactFieldTypeUnknown)
{
}

XQContactFieldPrivate::~XQContactFieldPrivate()
{
}

void XQContactFieldPrivate::setProperty(XQContactFieldPrivate::ContactFieldProperty property, bool enable)
{
    if (enable)
    {
        if (properties.indexOf(property) == -1)
        {
            properties.append(property);
        }
    }
    else
    {
        properties.removeOne(property);
    }
}

bool XQContactFieldPrivate::isProperty(XQContactFieldPrivate::ContactFieldProperty property) const
{
    if (properties.indexOf(property) != -1)
    {
        return true;
    }
    return false;
}

/// \endcond IGNORE

/*!
    \class XQContactField

    \brief The XQContactField class can be used for storing and handling contact
           field information (label, value and type).

*/

/*!
    Constructs a null contact field.
*/
XQContactField::XQContactField()
    : d(0)
{
}

/*!
    Constructs a new contact field using the given \a fieldType and \a value.

    \param fieldType The type of the field
    \param value The value of the field
*/
XQContactField::XQContactField(XQContactField::ContactFieldType fieldType, const QVariant& value)
    : d(new XQContactFieldPrivate)
{
    d->type = fieldType;
    d->value = value;
    d->ref.ref();
}

/*!
    Constructs a copy of \a other contact field.

    \param other The contact field to be copied
*/
XQContactField::XQContactField(const XQContactField& other)
    : d(other.d)
{
    if (d)
    {
        d->ref.ref();
    }
}

/*!
    Destroys the contact field.
*/
XQContactField::~XQContactField()
{
    if (d && !d->ref.deref())
    {
        delete d;
    }
}

/*!
    \return True if the field is empty; otherwise returns false.
*/
bool XQContactField::isNull() const
{
    return !d;
}

/*!
    Sets the field type for this field.

    \param fieldType The type of the field
    \sa value()
*/
void XQContactField::setType(XQContactField::ContactFieldType fieldType)
{
    detach();
    d->type = fieldType;
}

/*!

    \return The type of the field
    \sa setType()
*/
XQContactField::ContactFieldType XQContactField::type() const
{
    return d ? d->type : ContactFieldTypeUnknown;
}

/*!
    Sets the label of the field.

    \param  label The value to set for the field
    \sa value()
*/
void XQContactField::setLabel(const QString& label)
{
    detach();
    d->label = label;
}

/*!
    \return The label of the field
    \sa setLabel()
*/
QString XQContactField::label() const
{
    return d ? d->label : QString();
}

/*!
    Sets the value of the field.

    \param value the value of the field
    \sa value()
*/
void XQContactField::setValue(const QVariant& value)
{
    detach();
    d->value = value;
}

/*!
    \return The value of the field contents
    \sa setValue()
*/
QVariant XQContactField::value() const
{
    return d ? d->value : QVariant();
}

/*!
    Sets the id of the field.

    \param id The id to set for the field
    \sa value()
*/
void XQContactField::setId(int id)
{
    detach();
    d->id = id;
}

/*!
    \return the id of the field
    \sa setValue()
*/
int XQContactField::id() const
{
    return d ? d->id : -1;
}

/*!
    \return The field as a XQContactFieldAddress if the field has type() ContactFieldTypeAddress,
    ContactFieldTypePostOffice, ContactFieldTypeExtendedAddress, ContactFieldTypeLocality,
    ContactFieldTypeRegion, ContactFieldTypePostCode or ContactFieldTypeCountry;
    otherwise returns a null XQContactFieldAddress.
    
*/
XQContactFieldAddress XQContactField::toFieldAddress() const
{
    XQContactFieldAddress field;
    if (d && d->type >= ContactFieldTypeAddress && d->type <= ContactFieldTypeCountry)
    {
        field.d = d;
        d->ref.ref();
    }
    return field; 
}

/*!
    \return Returns the field as a XQContactFieldEmail if the field has type() ContactFieldTypeEMail;
    otherwise returns a null XQContactFieldEmail.
*/
XQContactFieldEmail XQContactField::toFieldEmail() const
{
    XQContactFieldEmail field;
    if (d && d->type == ContactFieldTypeEMail)
    {
        field.d = d;
        d->ref.ref();
    }
    return field;
}

/*!
    \return The field as a XQContactFieldPicture if the field has type() ContactFieldTypePicture;
    otherwise returns a null XQContactFieldPicture.
*/
XQContactFieldPicture XQContactField::toFieldPicture() const
{
    XQContactFieldPicture field;
    if (d && d->type == ContactFieldTypePicture)
    {
        field.d = d;
        d->ref.ref();
    }
    return field;
}

/*!
    \return The field as a XQContactFieldPhoneNumber if the field has type() ContactFieldTypePhoneNumber;
    otherwise returns a null XQContactFieldPhoneNumber.
*/
XQContactFieldPhoneNumber XQContactField::toFieldPhoneNumber() const
{
    XQContactFieldPhoneNumber field;
    if (d && d->type == ContactFieldTypePhoneNumber)
    {
        field.d = d;
        d->ref.ref();
    }
    return field;
}

/*!
    \returns The field as a XQContactFieldUrl if the field has type() ContactFieldUrl;
    otherwise returns a null XQContactFieldUrl.
*/
XQContactFieldUrl XQContactField::toFieldUrl() const
{
    XQContactFieldUrl field;
    if (d && d->type == ContactFieldTypeUrl)
    {
        field.d = d;
        d->ref.ref();
    }
    return field;
}

/*!
    \return The field as a XQContactFieldSipId if the field has type() ContactFieldTypeSIPID;
    otherwise returns a null XQContactFieldSipId.

*/
XQContactFieldSipId XQContactField::toFieldSipId() const
{
    XQContactFieldSipId field;
    if (d && d->type == ContactFieldTypeSIPID)
    {
        field.d = d;
        d->ref.ref();
    }
    return field;
}

/*!
    Assigns \a other contact field to this contact field and returns a reference
    to this contact field.

    \param other the other contact field
    \return a reference to this contact field
*/
XQContactField& XQContactField::operator=(const XQContactField& other)
{
    if (d == other.d)
    {
        return *this;
    }
    
    detach();
    d->label = other.d->label;
    d->value = other.d->value;
    d->properties = other.d->properties;
    d->type = other.d->type;
    return *this;
}

void XQContactField::detach()
{
    if (!d)
    {
        d = new XQContactFieldPrivate;
        d->ref = 1;
    }
    else
    {
        qAtomicDetach(d);
    }
}


/****************************************************
 *
 * XQContactFieldAddress
 *
 ****************************************************/

/*!
    \class XQContactFieldAddress

    \brief The XQContactFieldAddress class can be used for storing and handling
           information of contact address fields.
           XQContactFieldAddress inherits from XQContactField. Like XQContactField,
           XQContactFieldAddress is implicitly shared.
           In addition to XQContactField, XQContactFieldAddress provides possibility
           to handle address specific properties.

*/

/*!
    Constructs a null address field.
*/
XQContactFieldAddress::XQContactFieldAddress()
{
}

/*!
    Constructs a new address field using given \a fieldType and \a value.

    \param fieldType the type of the field
    \param value the value of the field
*/
XQContactFieldAddress::XQContactFieldAddress(XQContactField::ContactFieldType fieldType, const QVariant& value)
    : XQContactField(fieldType, value)
{
}

/*!
    Constructs a copy of \a other address field.

    \param other the address field to be copied
*/
XQContactFieldAddress::XQContactFieldAddress(const XQContactFieldAddress& other)
    : XQContactField(other)
{
}

/*!
    Destroys the address field.
*/
XQContactFieldAddress::~XQContactFieldAddress()
{
}

/*!
    Sets whether the address is the home address. If \a enable is true, the
    address is home address; otherwise, it is not.
    The default value is false.
    \param enable true if address is home address; false if not.

*/
void XQContactFieldAddress::setHome(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyHome, enable);
}

/*!
    \return Returns true if address is home address; otherwise returns false.

    \sa setHome()
*/
bool XQContactFieldAddress::isHome() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyHome) : false;
}

/*!
    Sets whether the address is work address. If \a enable is true, the
    address is work address; otherwise, it is not.
    The default value is false.
    \param enable true if address is work address; false if not. 

*/
void XQContactFieldAddress::setWork(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyWork, enable);
}

/*!
    \return true if address is work address; otherwise returns false.
    \sa setHome()
*/
bool XQContactFieldAddress::isWork() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyWork) : false;
}

/*!
    Sets whether the address is preferred address. If \a enable is true, the
    address is preferred address; otherwise, it is not.
    The default value is false.
    \param enable true if address is preferred address; false if not. 

*/
void XQContactFieldAddress::setPreferred(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPref, enable);
}

/*!
    \return True if address is preferred address; otherwise returns false.
    \sa setHome()
*/
bool XQContactFieldAddress::isPreferred() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyPref) : false;
}


/****************************************************
 *
 * XQContactFieldEmail
 *
 ****************************************************/
/*!
    \class XQContactFieldEmail

    \brief The XQContactFieldEmail class can be used for storing and handling
           information of contact email fields.
           XQContactFieldEmail inherits from XQContactField. Like XQContactField,
           XQContactFieldEmail is implicitly shared.
           In addition to XQContactField, XQContactFieldEmail provides possibility
           to handle email specific properties.

*/

/*!
    Constructs a null email field.
*/
XQContactFieldEmail::XQContactFieldEmail()
    : XQContactField()
{
}

/*!
    Constructs a new email field using the given \a value.

    \param value the value of the field
*/
XQContactFieldEmail::XQContactFieldEmail(const QVariant& value)
    : XQContactField(ContactFieldTypeEMail, value)
{
}

/*!
    Constructs a copy of \a other email field.

    \param other the email field to be copied
*/
XQContactFieldEmail::XQContactFieldEmail(const XQContactFieldEmail& other)
    : XQContactField(other)
{
}

/*!
    Destroys the email field.
*/
XQContactFieldEmail::~XQContactFieldEmail()
{
}

/*!
    Sets whether the email is the home email. If \a enable is true, the
    email is home email; otherwise, it is not.
    The default value is false.
    \param enable true if email is home email; false if not. 

*/
void XQContactFieldEmail::setHome(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyHome, enable);
}

/*!
    \return True if the email is the home email; otherwise returns false.

    \sa setHome()
*/
bool XQContactFieldEmail::isHome() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyHome) : false;
}

/*!
    Sets whether the email is work email. If \a enable is true, the
    email is work email; otherwise, it is not.
    The default value is false.
    \param enable true if email is work email; false if not. 

*/
void XQContactFieldEmail::setWork(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyWork, enable);
}

/*!
    \return True if email is work email; otherwise returns false.

    \return true if email is work email; otherwise returns false.
    \sa setHome()
*/
bool XQContactFieldEmail::isWork() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyWork) : false;
}

/*!
    Sets whether the email is the preferred email. If \a enable is true, the
    email is preferred email; otherwise, it is not.
    The default value is false.
    \param enable true if email is preferred email; false if not. 

*/
void XQContactFieldEmail::setPreferred(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPref, enable);
}

/*!
    \return True if this email is the preferred email; otherwise returns false.

    \sa setHome()
*/
bool XQContactFieldEmail::isPreferred() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyPref) : false;
}

void XQContactFieldEmail::detach()
{
    if (!d)
    {
        d = new XQContactFieldPrivate;
        d->type = ContactFieldTypeEMail;
        d->ref = 1;
    }
    else
    {
        qAtomicDetach(d);
    }
}


/****************************************************
 *
 * XQContactFieldPicture
 *
 ****************************************************/
/*!
    \class XQContactFieldPicture

    \brief The XQContactFieldPicture class can be used for storing and handling
           information of contact picture fields.
           XQContactFieldPicture inherits from XQContactField. Like XQContactField,
           XQContactFieldPicture is implicitly shared.
           In addition to XQContactField, XQContactFieldPicture provides possibility
           to handle picture type.
           
           Note: The value can be either image data (QImage, QByteArray...) or the full path
                 to an image file.
 
*/

/*!
    Constructs a null picture field.
*/
XQContactFieldPicture::XQContactFieldPicture()
    : XQContactField()
{
}

/*!
    Constructs a new picture field using the given \a value.
    \a value can be either image data (QImage, QByteArray...) or the full file path to an image.

    \param value The value of the field (either image data or file path to image)
*/
XQContactFieldPicture::XQContactFieldPicture(const QVariant& value)
    : XQContactField(ContactFieldTypePicture, value)
{
}

/*!
    Constructs a copy of \a other picture field.

    \param other The picture field to be copied
*/
XQContactFieldPicture::XQContactFieldPicture(const XQContactFieldPicture& other)
    : XQContactField(other)
{
}

/*!
    Destroys the picture field.
*/
XQContactFieldPicture::~XQContactFieldPicture()
{
}

/*!
    Sets the type of the stored picture.

    \param type The type of the stored picture.
*/
void XQContactFieldPicture::setPictureType(XQContactFieldPicture::ContactFieldPictureType type)
{
    detach();
    d->properties.clear();
    switch (type)
    {
        case ContactFieldPictureTypeGif:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyGif, true);
            break;
        case ContactFieldPictureTypeCgm:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyCgm, true);
            break;
        case ContactFieldPictureTypeWmf:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyWmf, true);
            break;
        case ContactFieldPictureTypeBmp:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyBmp, true);
            break;
        case ContactFieldPictureTypeDib:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyDib, true);
            break;
        case ContactFieldPictureTypePs:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPs, true);
            break;
        case ContactFieldPictureTypePmb:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPmb, true);
            break;
        case ContactFieldPictureTypePdf:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPdf, true);
            break;
        case ContactFieldPictureTypePict:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPict, true);
            break;
        case ContactFieldPictureTypeTiff:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyTiff, true);
            break;
        case ContactFieldPictureTypeJpeg:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyJpeg, true);
            break;
        case ContactFieldPictureTypeMet:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyMet, true);
            break;
        case ContactFieldPictureTypeMpeg:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyMpeg, true);
            break;
        case ContactFieldPictureTypeMpeg2:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyMpeg2, true);
            break;
        case ContactFieldPictureTypeAvi:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyAvi, true);
            break;
        case ContactFieldPictureTypeQTime:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyQTime, true);
            break;
        default:
            break;
    }
}

/*!
    \return The type of the stored picture.
    \sa setPictureType()
*/
XQContactFieldPicture::ContactFieldPictureType XQContactFieldPicture::pictureType() const
{
    if (!d)
    {
        return ContactFieldPictureTypeNotSet;
    }
    if (d->properties.count() > 0)
    {
        XQContactFieldPrivate::ContactFieldProperty property = d->properties.first();
        switch (property)
        {
            case XQContactFieldPrivate::ContactFieldPropertyGif:   return ContactFieldPictureTypeGif;
            case XQContactFieldPrivate::ContactFieldPropertyCgm:   return ContactFieldPictureTypeCgm;
            case XQContactFieldPrivate::ContactFieldPropertyWmf:   return ContactFieldPictureTypeWmf;
            case XQContactFieldPrivate::ContactFieldPropertyBmp:   return ContactFieldPictureTypeBmp;
            case XQContactFieldPrivate::ContactFieldPropertyDib:   return ContactFieldPictureTypeDib;
            case XQContactFieldPrivate::ContactFieldPropertyPs:    return ContactFieldPictureTypePs;
            case XQContactFieldPrivate::ContactFieldPropertyPmb:   return ContactFieldPictureTypePmb;
            case XQContactFieldPrivate::ContactFieldPropertyPdf:   return ContactFieldPictureTypePdf;
            case XQContactFieldPrivate::ContactFieldPropertyPict:  return ContactFieldPictureTypePict;
            case XQContactFieldPrivate::ContactFieldPropertyTiff:  return ContactFieldPictureTypeTiff;
            case XQContactFieldPrivate::ContactFieldPropertyJpeg:  return ContactFieldPictureTypeJpeg;
            case XQContactFieldPrivate::ContactFieldPropertyMet:   return ContactFieldPictureTypeMet;
            case XQContactFieldPrivate::ContactFieldPropertyMpeg:  return ContactFieldPictureTypeMpeg;
            case XQContactFieldPrivate::ContactFieldPropertyMpeg2: return ContactFieldPictureTypeMpeg2;
            case XQContactFieldPrivate::ContactFieldPropertyAvi:   return ContactFieldPictureTypeAvi;
            case XQContactFieldPrivate::ContactFieldPropertyQTime: return ContactFieldPictureTypeQTime;
            default: return ContactFieldPictureTypeNotSet;
        }
    }
    else
    {
        return ContactFieldPictureTypeNotSet;
    }
}

/*!
    \return True if field contains path to image; otherwise returns false.
*/
bool XQContactFieldPicture::isPath() const
{
    if (d && value().type() == QVariant::String)
    {
        return true;
    }
    return false;
}

/*!
    \return True if field contains image; otherwise returns false.
*/
bool XQContactFieldPicture::isImage() const
{
    if (d && value().type() != QVariant::String)
    {
        return true;
    }
    return false;
}

/*!
    Returns field value as QImage. If the field contains a path to an image,
    a QImage is automatically loaded from the path. If the field
    contains image data, data is loaded to image.

    \return The QImage on success; null image on failure
*/
QImage XQContactFieldPicture::valueAsImage() const
{
    QImage image;
    if (d)
    {
        if (value().type() == QVariant::String)
        {
            image.load(value().toString());
        }
        else
        {
            if (value().canConvert<QByteArray>())
            {
                image.loadFromData(value().toByteArray());
            }
        }
    }
    return image;
}

void XQContactFieldPicture::detach()
{
    if (!d)
    {
        d = new XQContactFieldPrivate;
        d->type = ContactFieldTypePicture;
        d->ref = 1;
    }
    else
    {
        qAtomicDetach(d);
    }
}


/****************************************************
 *
 * XQContactFieldPhoneNumber
 *
 ****************************************************/
/*!
    \class XQContactFieldPhoneNumber

    \brief The XQContactFieldPhoneNumber class can be used for storing and handling
           information about contact phone number fields.
           XQContactFieldPhoneNumber inherits from XQContactField. Like XQContactField,
           XQContactFieldPhoneNumber is implicitly shared.
           XQContactFieldPhoneNumber provides phone number specific properties
           in addition to the XQContactField properties, 

*/

/*!
    Constructs a null phone number field.
*/
XQContactFieldPhoneNumber::XQContactFieldPhoneNumber()
    : XQContactField()
{
}

/*!
    Constructs a new phone number field using given \a value.

    \param value the value of the field
*/
XQContactFieldPhoneNumber::XQContactFieldPhoneNumber(const QVariant& value)
    : XQContactField(ContactFieldTypePhoneNumber, value)
{
}

/*!
    Constructs a copy of \a other phone number field.

    \param other The phone number field to be copied
*/
XQContactFieldPhoneNumber::XQContactFieldPhoneNumber(const XQContactFieldPhoneNumber& other)
    : XQContactField(other)
{
}

/*!
    Destroys the phone number field.
*/
XQContactFieldPhoneNumber::~XQContactFieldPhoneNumber()
{
}

/*!
    Sets whether the phone number is a home phone number. If \a enable is true, the
    phone number is set as a home phone number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is to be set as a home phone number; false if not. 
    \sa isHome()
*/
void XQContactFieldPhoneNumber::setHome(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyHome, enable);
}

/*!
    \return True if the phone number is a home phone number; otherwise returns false.
    \sa setHome()
*/
bool XQContactFieldPhoneNumber::isHome() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyHome) : false;
}

/*!
    Sets whether the phone number is a work phone number. If \a enable is true, the
    phone number is to be set as a work phone number; otherwise, it is not.
    The default value is false.
    
    \param enable True if phone number is to be set as a work phone number; false if not. 
    \sa isWork()
*/
void XQContactFieldPhoneNumber::setWork(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyWork, enable);
}

/*!
    \return True if the phone number is a work phone number; otherwise returns false.
    \sa setWork()
*/
bool XQContactFieldPhoneNumber::isWork() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyWork) : false;
}

/*!
    Sets whether the phone number is the preferred phone number. If \a enable is true, the
    phone number is to be set as the preferred phone number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is to be set as the preferred phone number; false if not. 
    \sa isPreferred()
*/
void XQContactFieldPhoneNumber::setPreferred(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPref, enable);
}

/*!
    \return True if the phone number is the preferred phone number; otherwise returns false.
    \sa setPreferred()
*/
bool XQContactFieldPhoneNumber::isPreferred() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyPref) : false;
}

/*!
    Sets whether the phone number is a voice phone number. If \a enable is true, the
    phone number is to be set as a voice phone number; otherwise, it is not.
    The default value is false.

    \param enable True if the phone number is to be set as a voice phone number; false if not. 
    \sa isVoice()
*/
void XQContactFieldPhoneNumber::setVoice(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyVoice, enable);
}

/*!
    \return True if the phone number is a voice phone number; otherwise returns false.
    \sa setVoice()
*/
bool XQContactFieldPhoneNumber::isVoice() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyVoice) : false;
}

/*!
    Sets whether the phone number is cellular phone number. If \a enable is true, the
    phone number is to be set as a cellular phone number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is to set as a cellular phone number; false if not. 
    \sa isCellular()
*/
void XQContactFieldPhoneNumber::setCellular(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyCell, enable);
}

/*!
    \return True if the phone number is a cellular phone number; otherwise returns false.
    \sa setCellular()
*/
bool XQContactFieldPhoneNumber::isCellular() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyCell) : false;
}

/*!
    Sets whether the phone number is a pager number. If \a enable is true, the
    phone number is to be set as a pager number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is to be set as a pager number; false if not. 
    \sa isPager()
*/
void XQContactFieldPhoneNumber::setPager(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPager, enable);
}

/*!
    \return True if the phone number is a pager number; otherwise returns false.
    \sa setPager()
*/
bool XQContactFieldPhoneNumber::isPager() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyPager) : false;
}

/*!
    Sets whether the phone number is a BBS number. If \a enabled is true, the
    phone number is set as a BBS number; otherwise, it is not.
    The default value is false.
    
    \param enable True if phone number is to be made a BBS number; false if not. 
    \sa isBbs()
*/
void XQContactFieldPhoneNumber::setBbs(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyBbs, enable);
}

/*!
    \return True if the phone number is a BBS number; otherwise returns false.
    \sa setBbs()
*/
bool XQContactFieldPhoneNumber::isBbs() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyBbs) : false;
}

/*!
    Sets whether the phone number is a modem number. If \a enable is true, the
    phone number is set to be a modem number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is to be set as a modem number; false if not. 
    \sa isModem()
*/
void XQContactFieldPhoneNumber::setModem(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyModem, enable);
}

/*!
    \return True if the phone number is a modem number; otherwise returns false.
    \sa setModem()
*/
bool XQContactFieldPhoneNumber::isModem() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyModem) : false;
}

/*!
    Sets whether the phone number is car phone number. If \a enable is true, the
    phone number is set to be a car phone number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is a car phone number; false if not. 
    \sa isCar()
*/
void XQContactFieldPhoneNumber::setCar(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyCar, enable);
}

/*!
    \return True if the phone number is a car phone number; otherwise returns false.
    \sa setCar()
*/
bool XQContactFieldPhoneNumber::isCar() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyCar) : false;
}

/*!
    Sets whether the phone number is an ISDN number. If \a enable is true, the
    phone number is set to be an ISDN number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is to be set as an ISDN number; false if not. 
    \sa isIsdn()
*/
void XQContactFieldPhoneNumber::setIsdn(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyIsdn, enable);
}

/*!
    \return True if the phone number is an ISDN number; otherwise returns false.
    \sa setIsdn()
*/
bool XQContactFieldPhoneNumber::isIsdn() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyIsdn) : false;
}

/*!
    Sets whether the phone number is a video phone number. If \a enable is true, the
    phone number is set to be a video phone number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is a video phone number; false if not. 
    \sa isVideo()
*/
void XQContactFieldPhoneNumber::setVideo(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyVideo, enable);
}

/*!
    \return Returns true if the phone number is a video phone number; otherwise returns false.
    \sa setVideo()
*/
bool XQContactFieldPhoneNumber::isVideo() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyVideo) : false;
}

/*!
    Sets whether the phone number has voice messaging support. If \a enable is true,
    the phone number is set to have voice messaging support; otherwise, it does not have.
    The default value is false.
    
    \param enable True if phone number is to be set to have voice messaging support; false if not. 
    \sa isMessage()
*/
void XQContactFieldPhoneNumber::setMessage(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyMsg, enable);
}

/*!
    \return True if the phone number has voice messaging support; otherwise returns false.
    \sa setMessage()
*/
bool XQContactFieldPhoneNumber::isMessage() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyMsg) : false;
}

/*!
    Sets whether the phone number is a fax number. If \a enable is true, the
    phone number is set to be a fax number; otherwise, it is not.
    The default value is false.
    
    \param enable True if the phone number is set to be a fax number; false if not. 
    \sa isFax()
*/
void XQContactFieldPhoneNumber::setFax(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyFax, enable);
}

/*!
    \return True if the phone number is a fax number; otherwise returns false.
    \sa setVideo()
*/
bool XQContactFieldPhoneNumber::isFax() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyFax) : false;
}

void XQContactFieldPhoneNumber::detach()
{
    if (!d)
    {
        d = new XQContactFieldPrivate;
        d->type = ContactFieldTypePhoneNumber;
        d->ref = 1;
    }
    else
    {
        qAtomicDetach(d);
    }
}


/****************************************************
 *
 * XQContactFieldUrl
 *
 ****************************************************/
/*!
    \class XQContactFieldUrl

    \brief The XQContactFieldUrl class can be used for storing and handling
           information of contact URL fields.
           XQContactFieldUrl inherits from XQContactField. Like XQContactField,
           XQContactFieldUrl is implicitly shared.
           XQContactFieldUrl gives you access
           to URL specific properties in addition to the XQContactField properties,.

*/

/*!
    Constructs a null URL field.
*/
XQContactFieldUrl::XQContactFieldUrl()
    : XQContactField()
{
}

/*!
    Constructs a new URL field using given \a value.

    \param value The value of the field
*/
XQContactFieldUrl::XQContactFieldUrl(const QVariant& value)
    : XQContactField(ContactFieldTypeUrl, value)
{
}

/*!
    Constructs a copy of \a other URL field.

    \param other The URL field to be copied
*/
XQContactFieldUrl::XQContactFieldUrl(const XQContactFieldUrl& other)
    : XQContactField(other)
{
}

/*!
    Destroys the URL field.
*/
XQContactFieldUrl::~XQContactFieldUrl()
{
}

/*!
    Sets whether the URL is a home URL. If \a enable is true, the
    URL is set to be the home URL; otherwise, it is not.
    The default value is false.
    
    \param enable True if the URL is to be set as a home URL; false if not. 
    \sa isHome()
*/
void XQContactFieldUrl::setHome(bool enable)
{
    detach();
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyHome, enable);
}

/*!
    \return true if the URL is a home URL; otherwise returns false.

    \sa setHome()
*/
bool XQContactFieldUrl::isHome() const
{
    return d ? d->isProperty(XQContactFieldPrivate::ContactFieldPropertyHome) : false;
}

/*!
    Sets whether the URL is a work URL. If \a enable is true, the
    URL is work URL; otherwise, it is not.
    The default value is false.
    
    \param enable true if URL is work URL; false if not.
    \sa isWork()
*/
void XQContactFieldUrl::setWork(bool enable)
{
    d->setProperty(XQContactFieldPrivate::ContactFieldPropertyWork, enable);
}

/*!
    \return True if the URL is a work URL; otherwise returns false.
    \sa setWork()
*/
bool XQContactFieldUrl::isWork() const
{
    return d->isProperty(XQContactFieldPrivate::ContactFieldPropertyWork);
}

void XQContactFieldUrl::detach()
{
    if (!d)
    {
        d = new XQContactFieldPrivate;
        d->type = ContactFieldTypeUrl;
        d->ref = 1;
    }
    else
    {
        qAtomicDetach(d);
    }
}


/****************************************************
 *
 * XQContactFieldSipId
 *
 ****************************************************/
/*!
    \class XQContactFieldSipId

    \brief The XQContactFieldSipId class can be used for storing and handling
           information of contact SIPID fields.
           XQContactFieldSipId inherits from XQContactField. Like XQContactField,
           XQContactFieldSipId is implicitly shared.
           XQContactFieldSipId provides SIPID specific properties in addition to the XQContactField properties.

*/

/*!
    Constructs a null SIPID field.
*/
XQContactFieldSipId::XQContactFieldSipId()
    : XQContactField()
{
}

/*!
    Constructs a new SIPID field using the given \a value.

    \param value The value of the field
*/
XQContactFieldSipId::XQContactFieldSipId(const QVariant& value)
    : XQContactField(ContactFieldTypeSIPID, value)
{
}

/*!
    Constructs a copy of \a other SIPID field.

    \param other The SIPID field to be copied
*/
XQContactFieldSipId::XQContactFieldSipId(const XQContactFieldSipId& other)
    : XQContactField(other)
{
}

/*!
    Destroys the SIPID field.
*/
XQContactFieldSipId::~XQContactFieldSipId()
{
}

/*!
    Sets the type of the SIPID.

    \param type The type of the SIPID.
*/
void XQContactFieldSipId::setSipType(XQContactFieldSipId::ContactFieldSipType type)
{
    detach();
    d->properties.clear();
    switch (type)
    {
        case ContactFieldSipTypePoc:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyPoc, true);
            break;
        case ContactFieldSipTypeSwis:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertySwis, true);
            break;
        case ContactFieldSipTypeVoip:
            d->setProperty(XQContactFieldPrivate::ContactFieldPropertyVoip, true);
            break;
        default:
            break;
    }
}

/*!
    \return The type of the SIPID.
    \sa setSipType()
*/
XQContactFieldSipId::ContactFieldSipType XQContactFieldSipId::sipType() const
{
    if (!d)
    {
        return ContactFieldSipTypeNotSet;
    }
    if (d->properties.count() > 0)
    {
        XQContactFieldPrivate::ContactFieldProperty property = d->properties.first();
        switch (property)
        {
            case XQContactFieldPrivate::ContactFieldPropertyPoc:  return ContactFieldSipTypePoc;
            case XQContactFieldPrivate::ContactFieldPropertySwis: return ContactFieldSipTypeSwis;
            case XQContactFieldPrivate::ContactFieldPropertyVoip: return ContactFieldSipTypeVoip;
            default: return ContactFieldSipTypeNotSet;
        }
    }
    else
    {
        return ContactFieldSipTypeNotSet;
    }
}

void XQContactFieldSipId::detach()
{
    if (!d)
    {
        d = new XQContactFieldPrivate;
        d->type = ContactFieldTypeSIPID;
        d->ref = 1;
    }
    else
    {
        qAtomicDetach(d);
    }
}

// End of file
