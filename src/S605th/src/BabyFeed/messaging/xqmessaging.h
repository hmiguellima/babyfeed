#ifndef XQMESSAGING_H
#define XQMESSAGING_H

// INCLUDES
#include <QObject>
#include <QString>
#include <QStringList>
#include "messaging_global.h"

// FORWARD DECLARATIONS
class XQMessage;
class XQEmailAccount;
class XQMessagingPrivate;

// CLASS DECLARATION
class XQMESSAGING_EXPORT XQMessaging : public QObject
{
    Q_OBJECT

public:
    enum Error 
    {
        NoError = 0,
        OutOfMemoryError,
        NullMessageBodyError,
        ReceiverNotDefinedError,
        InternalError,
        NoAccountError,
        UnknownError = -1
    };

    enum MsgTypeFlag 
    {
        MsgTypeNotDefined = 0x00000000,
        MsgTypeSMS        = 0x00000001,
        MsgTypeMMS        = 0x00000002,
        MsgTypeEmail      = 0x00000004
    };
    Q_DECLARE_FLAGS(MsgType, MsgTypeFlag)

    XQMessaging(QObject* parent = 0);
    ~XQMessaging();

    bool send(const XQMessage& message);
    void setEmailAccount(const XQEmailAccount& emailAccount);
    QList<XQEmailAccount> emailAccounts();
    
    XQMessaging::Error error() const;

Q_SIGNALS:
    void error(XQMessaging::Error errorCode);
    void messageReceived(const XQMessage& message);

public Q_SLOTS:
    bool startReceiving(XQMessaging::MsgType);
    void stopReceiving();

private:
    friend class XQMessagingPrivate;
    XQMessagingPrivate* d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(XQMessaging::MsgType)

class XQMESSAGING_EXPORT XQMessage
{
public:
    enum ReceiverType
    {
        RecipientTo,
        RecipientCc,
        RecipientBcc    
    };
    
    XQMessage();
    XQMessage(const QStringList& receivers, const QString& body);
    XQMessage(const QStringList& receivers, const QString& body, const QStringList& attachmentPaths);
    XQMessage(const QStringList& receivers, const QString& body, const QString& subject);
    virtual ~XQMessage();

    virtual void setReceivers(const QStringList& receivers, XQMessage::ReceiverType type = XQMessage::RecipientTo);
    virtual void setBody(const QString& body);
    virtual void setSubject(const QString& subject);
    virtual void setAttachments(const QStringList& attachmentPaths);
    virtual void setSender(const QString& sender);
    virtual void setType(XQMessaging::MsgType type);
    virtual QStringList receivers(XQMessage::ReceiverType type = XQMessage::RecipientTo) const;
    virtual QString body() const;
    virtual QString subject() const;
    virtual QStringList attachments() const;
    virtual QString sender() const;
    virtual XQMessaging::MsgType type() const;

private: // Data
    QStringList m_msgreceivers;
    QStringList m_bccmsgreceivers;
    QStringList m_ccmsgreceivers;
    QString     m_msgsubject;
    QString     m_msgbody;
    QStringList m_msgattachmentPaths;
    QString     m_msgsender;
    XQMessaging::MsgType m_msgtype;
};

class XQMESSAGING_EXPORT XQEmailAccount
{  
public:
    XQEmailAccount();
        
    QString emailAlias() const;
    QString emailAddress() const;
    QString loginName() const;
    QString loginPassword() const;
    QString serverAddress() const;
    QString name() const;
    int port() const;

    
private: //Data
    QString m_emailAlias;
    QString m_emailAddress;
    QString m_loginName;
    QString m_loginPassword;
    QString m_serverAddress;
    QString m_name;
    int     m_port;
    int     m_id;
    
    friend class XQMessagingPrivate;
};

#endif // XQSMSMESSAGING_H

// End of file
