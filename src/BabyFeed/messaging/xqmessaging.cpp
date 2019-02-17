// INCLUDE FILES
#include "xqmessaging.h"
#ifdef Q_OS_SYMBIAN
#include "xqmessaging_s60_p.h"
#else
#include "xqmessaging_stub_p.h"
#endif

/****************************************************
 *
 * XQMessaging
 *
 ****************************************************/
/*!
    \class XQMessaging

    \brief The XQMessaging class can be used to send SMS, MMS and email messages
    and also notify you of SMS and MMS messages being received.
*/

/*!
    Constructs an XQMessaging object with the given parent.
    \sa send()
*/
XQMessaging::XQMessaging(QObject * parent)
 : QObject(parent), d(new XQMessagingPrivate(this))
{
}

/*!
    Destroys the XQMessaging object.
*/
XQMessaging::~XQMessaging()
{
    delete d;
}

/*!
    \enum XQMessaging::Error

    This enum defines the possible errors for a XQMessaging object.
*/
/*! \var XQMessaging::Error XQMessaging::NoError
    No error occured.
*/
/*! \var XQMessaging::Error XQMessaging::OutOfMemoryError
    Not enough memory.
*/
/*! \var XQMessaging::Error XQMessaging::NullMessageBodyError
    Message body is null.
*/
/*! \var XQMessaging::Error XQMessaging::ReceiverNotDefinedError
    Receiver not defined in the message.
*/
/*! \var XQMessaging::Error XQMessaging::InternalError
    Internal error.
*/
/*! \var XQMessaging::Error XQMessaging::NoAccountError
    No email account exists.
*/
/*! \var XQMessaging::Error XQMessaging::UnknownError
    Unknown error.
*/

/*!
    \enum XQMessaging::MsgTypeFlag

    This enum defines the possible message types for a XQMessaging object.
*/
/*! \var XQMessaging::MsgTypeNotDefined XQMessaging::MsgTypeNotDefined
    Message type is not defined.
*/
/*! \var XQMessaging::MsgTypeSMS XQMessaging::MsgTypeSMS
    Message type is SMS.
*/
/*! \var XQMessaging::MsgTypeMMS XQMessaging::MsgTypeMMS
    Message type is MMS.
*/
/*! \var XQMessaging::MsgTypeEmail XQMessaging::MsgTypeEmail
    Message type is email.
*/

/*!
    Sends an SMS, MMS or email Message. If the message contains email address the message will be sent as email. 
    If the message contains an attachment (or several attachments) but not email address, 
    the message will be sent as MMS, otherwise the message will be sent as an SMS.

    \param message Message to be sent
    \return If false is returned, an error has occurred. Call error() to get a value of 
            XQMessaging::Error that indicates which error occurred
*/
bool XQMessaging::send(const XQMessage& message)
{
    return d->send(message);
}

/*!
    Starts notifying you of newly received messages. The messageReceived() signal is emitted 
    every time an SMS or MMS message is received.

    \param msgType the type for messages to be received (SMS or MMS or both)
    \return If false is returned, an error has occurred. Call error() to get a value of 
            XQMessaging::Error that indicates which error occurred

    \sa stopReceiving(), messageReceived()
*/
bool XQMessaging::startReceiving(XQMessaging::MsgType msgType)
{
    return d->startReceiving(msgType);
}

/*!
    Stops notifying you of newly received messages.

    \sa startReceiving()
*/
void XQMessaging::stopReceiving()
{
    d->stopReceiving();
}

/*!
    Sets the email account to be used for sending email messages.
    By default the default SMTP account will be used for sending email messages if exists.
    
    \param emailAccount The email account
*/
void XQMessaging::setEmailAccount(const XQEmailAccount& emailAccount)
{
    d->setEmailAccount(emailAccount);
}

/*!
    \return The list of the accounts in the device
    \sa setReceivers()
*/
QList<XQEmailAccount> XQMessaging::emailAccounts()
{
    return d->emailAccounts();
}

/*!
    Returns the type of error that occurred if the latest function call failed; otherwise returns NoError.
    
    \return Error code
*/
XQMessaging::Error XQMessaging::error() const
{
    return d->error();
}

/*!
    \fn void XQMessaging::messageReceived(const XQMessage& message)

    This signal is emitted when a new message is received.

    \param message a received message
    \sa startReceiving(), stopReceiving()
*/

/*!
    \fn void XQMessaging::error(XQMessaging::Error errorCode)

    This signal is emitted when an error has occured.

    \param errorCode a error code
    \sa startReceiving()
*/


/****************************************************
 *
 * XQMessage
 *
 ****************************************************/
/*!
    \class XQMessage

    \brief The XQMessage class can be used to construct an SMS, MMS or Email Message.
*/

/*!
    Constructs an empty XQMessage object.
*/
XQMessage::XQMessage()
    : m_msgtype(XQMessaging::MsgTypeNotDefined)
{
}

/*!
    Constructs a new SMS XQMessage object with the specified receivers and body.
    
    \param receivers A list of the intended recipients of the message
    \param body The body of the message to be sent
*/
XQMessage::XQMessage(const QStringList& receivers, const QString& body)
    : m_msgreceivers(receivers),
      m_msgbody(body),
      m_msgtype(XQMessaging::MsgTypeSMS)
{
}

/*!
    Constructs a new Email XQMessage object with the specified receivers, body and subject.
    
    \param receivers A list of the intended recipients of the message
    \param body The body of the message to be sent
    \param subject The message subject
*/
XQMessage::XQMessage(const QStringList& receivers, const QString& body, const QString& subject)
    : m_msgreceivers(receivers),
      m_msgbody(body),
      m_msgsubject(subject),
      m_msgtype(XQMessaging::MsgTypeEmail)
{
}

/*!
    Constructs a new MMS XQMessage object with specified receivers, body and attachments.
    
    \param receivers A list of the intended recipients of the message
    \param body The body of the message to be sent
    \param attachmentPaths A list of fully specified paths to the files that will be attached to the MMS message 
*/
XQMessage::XQMessage(const QStringList& receivers, const QString& body, const QStringList& attachmentPaths)
    : m_msgreceivers(receivers),
      m_msgbody(body),
      m_msgattachmentPaths(attachmentPaths),
      m_msgtype(XQMessaging::MsgTypeMMS)
{
}

/*!
    Destroys the XQMessage object.
*/
XQMessage::~XQMessage()
{
}

/*!
    Sets receivers of the message.

    \param receivers A list of the intended recipients of the message
    \param type Optional parameter for the email messages which defines type of the receivers (To, CC and BCC)
    \sa receivers()
*/
void XQMessage::setReceivers(const QStringList& receivers, XQMessage::ReceiverType type)
{
    switch(type)
    {
        case RecipientTo:
        {
            m_msgreceivers = receivers;
            break;
        }
        case RecipientCc:
        {
            m_ccmsgreceivers = receivers;
            break;    
        }
        case RecipientBcc:
        {
            m_bccmsgreceivers = receivers;
            break;    
        }
        default:
        {
            m_msgreceivers = receivers;
        }
    }
}

/*!
    Sets the body of the message.

    \param body the body of the message
    \sa body()
*/
void XQMessage::setBody(const QString& body)
{
    m_msgbody = body;
}

/*!
    Sets the subject line of the message.

    \param subject The subject line of the message
    \sa subject()
*/
void XQMessage::setSubject(const QString& subject)
{
    m_msgsubject = subject;
}

/*!
    Sets the attachments of the message.

    \param attachmentPaths A list of fully specified paths to the files that will be attached to the MMS message 
    \sa attachments()
*/
void XQMessage::setAttachments(const QStringList& attachmentPaths)
{
    m_msgattachmentPaths = attachmentPaths;
}

/*!
    Sets the sender of the message.

    \param sender The sender of the message
    \sa sender()
*/
void XQMessage::setSender(const QString& sender)
{
    m_msgsender = sender;
}

/*!
    Sets the type of the message.

    \param type The XQMessaging::MsgType type of the message
    \sa type()
*/
void XQMessage::setType(XQMessaging::MsgType type)
{
    m_msgtype = type;
}

/*!

    \return The list of the intended recipients of the message
    \sa setReceivers()
    \par type Carbon copy and blind carbon copy recipients can be defined in case of email.
*/
QStringList XQMessage::receivers(XQMessage::ReceiverType type) const
{
    switch(type)
    {
        case RecipientTo:
        {
            return m_msgreceivers;
        }
        case RecipientCc:
        {
            return m_ccmsgreceivers;   
        }
        case RecipientBcc:
        {
            return m_bccmsgreceivers; 
        }
        default:
        {
            return QStringList();
        }
    }
}

/*!
    \return The body of the message
    \sa setBody()
*/
QString XQMessage::body() const
{
    return m_msgbody;
}

/*!
    \return The subject line of the message
    \sa setSubject()
*/
QString XQMessage::subject() const
{
    return m_msgsubject;
}

/*!
    \return A list of fully specified paths to the files that will are attached to the MMS message 
    \sa setAttachments()
*/
QStringList XQMessage::attachments() const
{
    return m_msgattachmentPaths;
}

/*!
    \return The sender of the message
    \sa setSender()
*/
QString XQMessage::sender() const
{
    return m_msgsender;
}

/*!

    \return The XQMessaging::MsgType type of the message
    \sa setType()
*/
XQMessaging::MsgType XQMessage::type() const
{
    return m_msgtype;
}

/****************************************************
 *
 * XQEmailAccount
 *
 ****************************************************/
/*!
    \class XQEmailAccount

    \brief The XQEmailAccount class can be used to get info about the specific account.
*/

/*!
    Constructs an empty XQEmailAccount object.
*/
XQEmailAccount::XQEmailAccount() : m_id(-1)
{   
}
    
/*!
    \return The email alias
*/
QString XQEmailAccount::emailAlias() const
{
    return m_emailAlias;
}

/*!
    \return The email address
*/
QString XQEmailAccount::emailAddress() const
{
    return m_emailAddress;
}

/*!
    \return The login name
*/
QString XQEmailAccount::loginName() const
{
    return m_loginName;
}

/*!
    \return The login password
*/
QString XQEmailAccount::loginPassword() const
{
    return m_loginPassword;
}

/*!
    \return The address of the server
*/
QString XQEmailAccount::serverAddress() const
{
    return m_serverAddress;
}

/*!
    \return The name of the account
*/
QString XQEmailAccount::name() const
{
    return m_name;
}

/*!
    \return The port of the server
*/
int XQEmailAccount::port() const
{
    return m_port;
}

// End of file
