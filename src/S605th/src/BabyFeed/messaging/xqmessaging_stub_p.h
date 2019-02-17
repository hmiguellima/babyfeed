#ifndef XQMESSAGING_STUB_P_H
#define XQMESSAGING_STUB_P_H

// INCLUDES
#include "private/qobject_p.h"
#include "xqsmsmessaging.h"

// CLASS DECLARATION
class XQMessagingPrivate : public QObjectPrivate, CBase
{
    Q_DECLARE_PUBLIC(XQSMSMessaging)

public:
    XQMessagingPrivate();
    ~XQMessagingPrivate();

    XQMessaging::Error send(const XQMessage& message);
    void setEmailAccount(const XQEmailAccount& emailAccount);
    QList<XQEmailAccount> emailAccounts();
    void startReceiving(XQMessaging::MsgType msgType);
    void stopReceiving();

public: // Data
    int error;

private: // Data
};

#endif /* XQMESSAGING_STUB_P_H */

// End of file
