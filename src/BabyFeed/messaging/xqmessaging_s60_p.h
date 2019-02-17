#ifndef XQMESSAGING_S60_P_H
#define XQMESSAGING_S60_P_H

// INCLUDES
#include <private/qobject_p.h>
#include <QList>
#include <QString>
#include <msvapi.h>
#include <msvstd.h>
#include <cemailaccounts.h>
#include "xqmessaging.h"

// FORWARD DECLARATIONS
class XQSMSMessaging;
class CMsvSession;
class CMsvEntry;
class CSmsClientMtm;
class CMmsClientMtm;
class CClientMtmRegistry;
class CCharFormatLayer;
class CParaFormatLayer;
class CMsvSessionObserver;
class CSmtpClientMtm;

// CLASS DECLARATION
class XQMessagingPrivate : public CBase, public MMsvSessionObserver
{
public:
    XQMessagingPrivate(XQMessaging* apParent);
    ~XQMessagingPrivate();

    bool send(const XQMessage& message);
    void setEmailAccount(const XQEmailAccount& emailAccount);
    QList<XQEmailAccount> emailAccounts();
    bool startReceiving(XQMessaging::MsgType msgType);
    void stopReceiving();

    friend class CMsvSessionObserver;    
    
    XQMessaging::Error error() const;

private:

// Overriden function of session event.
//  Session observer, reports whatever notification it receives.
void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3); 
    void sendSMSL(const XQMessage& message);
    void sendMMSL(const XQMessage& message);
    void createAndSendEmailL(const XQMessage& message);
    void CreateClientRegistryL();
    void DeliverMessage(XQMessage& message);
    void DeliverError(XQMessaging::Error error);
    XQMessaging::Error initializeObserver(XQMessaging::MsgType msgType);
    void SendEmailL();
    void AddAttachmentL(const TFileName& fileName);

private: // Data
    CMsvSessionObserver*    ipObserver;
    XQMessaging*            ipParent;
    TSmtpAccount            iSmtpAccount;
    CMsvSession*            iSession;
    CClientMtmRegistry*     iClientRegistry;
    CSmtpClientMtm*         iSmtpMtm;
    XQEmailAccount          iEmailAccount;
    bool                    iClientRegistered;
    int                     iError;
};

class CMsvSessionObserver : public CActive, public MMsvSessionObserver
{
public: // Constructors and destructor
    static CMsvSessionObserver* NewL(XQMessagingPrivate* apParent, XQMessaging::MsgType msgType);
    ~CMsvSessionObserver();

private: // from MMsvSessionObserver
    void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1,
                             TAny* aArg2, TAny* aArg3);
    void DeliverMessagesL();

private: // from CActive
    void RunL();
    void DoCancel();

private: // Constructors
    CMsvSessionObserver(XQMessagingPrivate* apParent);
    void ConstructL(XQMessaging::MsgType msgType);

public: // Data
    bool                     iListenForIncomingMessages;
    XQMessaging::MsgType     iMsgType;

private: // Data
    TInt                     counter;                  
    XQMessagingPrivate*      ipParent;

    CCharFormatLayer*        ipCharFormatLayer;
    CParaFormatLayer*        ipParaFormatLayer;
    CRichText*               ipRichText;

    TBool                    iMsvSessionReady;
    CMsvSession*             ipMsvSession;      // Session with the messaging server
    CClientMtmRegistry*      ipClientMtmReg;
    CSmsClientMtm*           ipSmsMtm;
    CMmsClientMtm*           ipMmsMtm;
    
    CMsvEntrySelection*      ipReceivedMessages;
    RTimer                   iTimer;            // Timer used for delaying delivering of received messages
    
    TBuf<KMaxPath>           iPath;
};

#endif /* XQMESSAGING_S60_P_H */

// End of file
