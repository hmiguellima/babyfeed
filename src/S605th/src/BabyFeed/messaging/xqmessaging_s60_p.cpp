// INCLUDE FILES
#include "xqmessaging_s60_p.h"
#include <e32des16.h>
#include <rsendasmessage.h>
#include <rsendas.h>
#include <mtclreg.h>
#include <smut.h>
#include <mmsconst.h>
#include <smsclnt.h>        // CSmsClientMtm
#include <mmsclient.h>      // CMmsClientMtm 
#include <msvstore.h>       // CMsvStore
#include <txtrich.h>        // CRichText
#include <txtfmlyr.h>
#include <smuthdr.h>        // CSmsHeader
#include <utf.h>            // CnvUtfConverter
#include <MMsvAttachmentManager.h>
#include <CMsvAttachment.h>
#include <SendUiConsts.h>
#include <smtpset.h>
#include <iapprefs.h>
#include <miutset.h>
#include <smtcmtm.h>        //SMTCMTM.H 
#include <mtuireg.h>
#include <mtmuibas.h>
#include <cmsvmimeheaders.h> 
#include <miutmsg.h>

const TInt KWaitAfterReceivedMessage = 100000; // = 0.1 seconds

#ifdef __WINS__
const TMsvId KObservedFolderId = KMsvDraftEntryId;
#else
const TMsvId KObservedFolderId = KMsvGlobalInBoxIndexEntryId;
#endif

_LIT(KTitle, "Imap4example");
_LIT(KDataComponentFileName, "c:\\system\\mtm\\impc.dat" );
_LIT(KTextPressAKey, "\n\n Press any key to step through the example");
_LIT(KExit,"\n\n Press any key to exit the application ");
_LIT(KCreateMtm,"\n\n Creating an Imap4 client MTM");
_LIT(KTxtAccountName, "ImapAccount");
_LIT(KCreateAccounts,"\n\n Creating Imap and Smtp acoounts");
_LIT(KSmtpServerAddress, "ban-sindhub01.intra");
_LIT(KEmailAlias, "Messaging example");
_LIT(KSmtpEmailAddress, "ban-sindhub01@ban-sindhub01.intra");
_LIT8(KFrom, "ban-sindhub01@ban-sindhub01.intra");
_LIT(KTo, "ban-sindhub01@ban-sindhub01.intra");
_LIT(KSubject, "SimpleEmail");
_LIT(KBodyContents, "This is a very simple mail");
_LIT(KSendMail,"\n\n Sending the mail... please wait");
_LIT(KImapServer, "ban-sindhub01.intra");   
_LIT8(KImapPassword,"ban-sindhub01");
_LIT8(KImapLoginName,"ban-sindhub01");  
_LIT(KWait,"\n\n Connecting to the imap server");
_LIT(KPopulate,"\n\n Downloading........");
_LIT(KDisconnect,"\n\n Disconnecting from the imap server");

XQMessagingPrivate::XQMessagingPrivate(XQMessaging* apParent)
    : ipParent(apParent), iClientRegistered(false)
{
}

XQMessagingPrivate::~XQMessagingPrivate()
{
    delete ipObserver;
    delete iSession;
    delete iSmtpMtm;
    delete iClientRegistry;
}

bool XQMessagingPrivate::send(const XQMessage& message)
{
    TRAP(iError,
        if (message.type() == XQMessaging::MsgTypeSMS) 
        {
            sendSMSL(message);
        } 
        else if (message.type() == XQMessaging::MsgTypeMMS) 
        {
            sendMMSL(message);
        }
        else if (message.type() == XQMessaging::MsgTypeEmail || message.receivers().contains(QString("@")) || !message.subject().isNull()) 
        {
            createAndSendEmailL(message);
        }
        else if (message.attachments().count() > 0) 
        {
            sendMMSL(message);
        } 
        else 
        {
            sendSMSL(message);
        }
    );

    return (iError == KErrNone);
}

void XQMessagingPrivate::setEmailAccount(const XQEmailAccount& emailAccount)
{
    iEmailAccount = emailAccount;      
}

QList<XQEmailAccount> XQMessagingPrivate::emailAccounts()
{
    QList<XQEmailAccount> emailAccountsList;
    TRAP(iError,
        CEmailAccounts* emailAccounts = CEmailAccounts::NewLC();
        RArray<TSmtpAccount> smtpAccounts;
        CleanupClosePushL(smtpAccounts);
        emailAccounts->GetSmtpAccountsL(smtpAccounts);
        
        for (int i = 0; i < smtpAccounts.Count(); i++)
        {
            XQEmailAccount account;
            CImSmtpSettings* smtpSettings = new (ELeave) CImSmtpSettings();
            CleanupStack::PushL(smtpSettings);
            emailAccounts->LoadSmtpSettingsL(smtpAccounts[i], *smtpSettings);
            
            // Id
            account.m_id = smtpAccounts[i].iSmtpService; //iSmtpAccountId;
            
            // Name
            TPtrC accountName = smtpAccounts[i].iSmtpAccountName;
            account.m_name = QString::fromUtf16(accountName.Ptr(), accountName.Length());
            
            // Email alias
            TPtrC emailAlias = smtpSettings->EmailAlias();
            account.m_emailAlias = QString::fromUtf16(emailAlias.Ptr(), emailAlias.Length());
            
            // Email address
            TPtrC emailAddress = smtpSettings->EmailAddress();
            account.m_emailAddress = QString::fromUtf16(emailAddress.Ptr(), emailAddress.Length());
            
            // Login name
            TPtrC8 loginName = smtpSettings->LoginName();
            HBufC* loginNameTmp = CnvUtfConverter::ConvertToUnicodeFromUtf8L(loginName);
            account.m_loginName = QString::fromUtf16(loginNameTmp->Ptr(), loginNameTmp->Length());
            delete loginNameTmp;
    
            // Password
            TPtrC8 password = smtpSettings->Password();
            HBufC* passwordTmp = CnvUtfConverter::ConvertToUnicodeFromUtf8L(password);
            account.m_loginPassword = QString::fromUtf16(passwordTmp->Ptr(), passwordTmp->Length());
            delete passwordTmp;
    
            // Server port
            account.m_port = smtpSettings->Port();
            
            // Server address
            TPtrC serverAddress = smtpSettings->ServerAddress();
            account.m_serverAddress = QString::fromUtf16(serverAddress.Ptr(), serverAddress.Length());
            emailAccountsList.append(account);
            CleanupStack::PopAndDestroy(smtpSettings);
        }
        CleanupStack::PopAndDestroy(2, emailAccounts);
    )
    return emailAccountsList;
}

void XQMessagingPrivate::sendSMSL(const XQMessage& message)
{
    if (message.body().isNull()) 
    {
        User::Leave(XQMessaging::NullMessageBodyError);
    }
    if (message.receivers().count() == 0) 
    {
        User::Leave(XQMessaging::ReceiverNotDefinedError);
    }

    RSendAs sendAs;
    TInt err = sendAs.Connect();
    if (err) 
    {
        User::Leave(XQMessaging::InternalError);
    }
    CleanupClosePushL(sendAs);

    RSendAsMessage sendAsMessage;
    sendAsMessage.CreateL(sendAs, KUidMsgTypeSMS);
    CleanupClosePushL(sendAsMessage);

    // Prepare the message
    
    // Add receivers
    QStringListIterator i(message.receivers());
    TPtrC16 receiver(KNullDesC);
    QString qreceiver;
    while (i.hasNext()) 
    {
        qreceiver = i.next();
        receiver.Set(reinterpret_cast<const TUint16*>(qreceiver.utf16()));
        sendAsMessage.AddRecipientL(receiver, RSendAsMessage::ESendAsRecipientTo);
    }

    // Set Body text
    QString body = message.body();
    TPtrC16 msg(reinterpret_cast<const TUint16*>(body.utf16()));
    HBufC* bd = msg.AllocL();
    sendAsMessage.SetBodyTextL(*bd);
    
    // Send the message
    sendAsMessage.SendMessageAndCloseL();

    CleanupStack::Pop(); // sendAsMessage (already closed)
    CleanupStack::PopAndDestroy(); // sendAs
}

void XQMessagingPrivate::sendMMSL(const XQMessage& message)
{
    if (message.receivers().count() == 0) 
    {
        User::Leave(XQMessaging::ReceiverNotDefinedError);
    }

    RSendAs sendAs;
    TInt err = sendAs.Connect();
    if (err) 
    {
        User::Leave(XQMessaging::InternalError);
    }
    CleanupClosePushL(sendAs);

    RSendAsMessage sendAsMessage;
    sendAsMessage.CreateL(sendAs, KUidMsgTypeMultimedia);
    CleanupClosePushL(sendAsMessage);

    // Prepare the message
    
    // Add receivers
    QStringListIterator i(message.receivers());
    TPtrC16 receiver(KNullDesC);
    QString qreceiver;
    while (i.hasNext()) 
    {
        qreceiver = i.next();
        receiver.Set(reinterpret_cast<const TUint16*>(qreceiver.utf16()));
        sendAsMessage.AddRecipientL(receiver, RSendAsMessage::ESendAsRecipientTo);
    }
    
    // Set Subject
    QString subject = message.subject();
    TPtrC16 sbj(reinterpret_cast<const TUint16*>(subject.utf16()));
    sendAsMessage.SetSubjectL(sbj);

    // Set Body text
    QString body = message.body();
    TPtrC16 msg(reinterpret_cast<const TUint16*>(body.utf16()));
    HBufC8* pMsg = CnvUtfConverter::ConvertFromUnicodeToUtf8L(msg);
    
    RFs fileServer;
    User::LeaveIfError(fileServer.Connect());
    RFile file;
    TFileName tempFileName;
    // Temporary file will be written to private folder (because Path == KNullDesC)
    err = file.Temp(fileServer, KNullDesC, tempFileName, EFileWrite);
    if (err) 
    {
        User::Leave(XQMessaging::InternalError);
    }
    file.Write(*pMsg);
    file.Close();
    delete pMsg;
    
    TRequestStatus status;
    sendAsMessage.AddAttachment(tempFileName, _L8("text/plain"), status);
    User::WaitForRequest(status);
    
    if (message.attachments().count() > 0) 
    {
        // Add attachments
        TPtrC16 attachmentPath(KNullDesC);
        QString qattachmentPath;
        QStringListIterator j(message.attachments());
        while (j.hasNext()) 
        {
            qattachmentPath = j.next();
            attachmentPath.Set(reinterpret_cast<const TUint16*>(qattachmentPath.utf16()));
            sendAsMessage.AddAttachment(attachmentPath, status);
            User::WaitForRequest(status);
        }
    }
    fileServer.Delete(tempFileName);
    fileServer.Close();
    
    // Send the message
    sendAsMessage.SendMessageAndCloseL();

    CleanupStack::Pop(); // sendAsMessage (already closed)
    CleanupStack::PopAndDestroy(); // sendAs
}

void XQMessagingPrivate::CreateClientRegistryL()
{
    // Create a message server session 
    iSession = CMsvSession::OpenSyncL(*this);
    CleanupStack::PushL(iSession);
    
    // Create a client-side MTM registry
    iClientRegistry = CClientMtmRegistry::NewL(*iSession, KMsvDefaultTimeoutMicroSeconds32);
    if (iClientRegistry != NULL && iClientRegistry->IsPresent(KUidMsgTypeSMTP))
    {
        CleanupStack::PushL(iClientRegistry);
    }
    // Create a Client-side MTM object for the specified MTM UID.
    iSmtpMtm = (CSmtpClientMtm*)iClientRegistry->NewMtmL(KUidMsgTypeSMTP); 
    CleanupStack::Pop(2, iSession); // iClientRegistry, iSession
    
    iClientRegistered = true;
}

void XQMessagingPrivate::createAndSendEmailL(const XQMessage& message)
{
    if (message.receivers().count() == 0) 
    {
        User::Leave(XQMessaging::ReceiverNotDefinedError);
    }
    
    if (!iClientRegistered)
    {
        TRAP(iError, CreateClientRegistryL());
        if (iError != KErrNone)
        {
            User::Leave(XQMessaging::InternalError);    
        }
    }
    
    TMsvId outboxId = KMsvGlobalOutBoxIndexEntryId; 
        
    // Set the context to the folder in which message has to be created
    CMsvEntry*  entry = CMsvEntry::NewL(*iSession, outboxId, TMsvSelectionOrdering());
    CleanupStack::PushL(entry);
    entry->SetEntryL(outboxId);
    
    CMsvOperationWait* waiter = CMsvOperationWait::NewLC();
    
    TMsvEmailTypeList msvEmailTypeList = 0;
    TMsvPartList partList = (KMsvMessagePartBody | KMsvMessagePartAttachments);
    
    CImEmailOperation* emailOperation = CImEmailOperation::CreateNewL(waiter->iStatus, *iSession, KMsvGlobalOutBoxIndexEntryId, partList, msvEmailTypeList, KUidMsgTypeSMTP);
    CleanupStack::PushL(emailOperation);
    waiter->Start();
    CActiveScheduler::Start();
    
    TMsvId temp;
    TPckgC<TMsvId> paramPack(temp);
    const TDesC8& progBuf = emailOperation->ProgressL();
    paramPack.Set(progBuf);
    TMsvId newMessageId;
    newMessageId = paramPack();

    entry->SetEntryL(newMessageId);

    CParaFormatLayer* paragraphFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL(paragraphFormatLayer);

    CCharFormatLayer* characterFormatLayer = CCharFormatLayer::NewL(); 
    CleanupStack::PushL(characterFormatLayer);

    CRichText* bodyText = CRichText::NewL(paragraphFormatLayer, characterFormatLayer, CEditableText::EFlatStorage, 256);
    CleanupStack::PushL(bodyText);

    // Insert the contents of a buffer into the document at specified position
    bodyText->InsertL(0, TPtrC(reinterpret_cast<const TUint16*>(message.body().utf16())));
    
    CImEmailMessage* emailMessage = CImEmailMessage::NewL(*entry);
    CleanupStack::PushL(emailMessage);
    emailMessage->StoreBodyTextL(newMessageId, *bodyText, waiter->iStatus);
    waiter->Start();
    CActiveScheduler::Start();
    
    for (int i = 0; i < message.attachments().count(); i++)
    {
        RFs fs;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);
        RFile file;
        TPtrC attachment(reinterpret_cast<const TUint16*>(message.attachments().at(i).utf16()));
        User::LeaveIfError(file.Open(fs, attachment, EFileShareAny|EFileRead));
        CleanupClosePushL(file);
                   
        CMsvAttachment* attachmentInfo = CMsvAttachment::NewL(CMsvAttachment::EMsvFile);
        CleanupStack::PushL(attachmentInfo);
                   
        emailMessage->AttachmentManager().AddAttachmentL(file, attachmentInfo, waiter->iStatus);
        waiter->Start();
        CActiveScheduler::Start();
        CleanupStack::PopAndDestroy(3, &fs); // attachmentInfo, file, fs
    }

    CMsvStore* store = entry->EditStoreL();
    CleanupStack::PushL(store);
    CImHeader* emailEntry = CImHeader::NewLC();
    emailEntry->RestoreL(*store);
    emailEntry->SetSubjectL(TPtrC(reinterpret_cast<const TUint16*>(message.subject().utf16())));
    
    QStringListIterator i(message.receivers(XQMessage::RecipientTo));
    while (i.hasNext())
    {
        emailEntry->ToRecipients().AppendL(TPtrC(reinterpret_cast<const TUint16*>(i.next().utf16())));  
    }
    
    QStringListIterator j(message.receivers(XQMessage::RecipientCc));
    while (j.hasNext())
    {
        emailEntry->CcRecipients().AppendL(TPtrC(reinterpret_cast<const TUint16*>(j.next().utf16())));  
    }
    
    QStringListIterator k(message.receivers(XQMessage::RecipientBcc));
    while (k.hasNext())
    {
        emailEntry->BccRecipients().AppendL(TPtrC(reinterpret_cast<const TUint16*>(k.next().utf16())));  
    }
     
    emailEntry->StoreL(*store);
    // Store the changes permanently
    store->CommitL();

    CleanupStack::PopAndDestroy(9, entry); // emailmessage, bodyText, characterFormatLayer, paragraphFormatLayer, emailEntry, store, emailOperation, waiter, entry

    SendEmailL();
}

void XQMessagingPrivate::HandleSessionEventL(TMsvSessionEvent /*aEvent*/, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/)
{
}

void XQMessagingPrivate::SendEmailL()
{
    CEmailAccounts* emailAccounts = CEmailAccounts::NewLC();
    CMsvEntry* entry = NULL;
    
    if (iEmailAccount.m_id != -1)
    {
        emailAccounts->GetSmtpAccountL(iEmailAccount.m_id, iSmtpAccount);
        entry = iSession->GetEntryL(iEmailAccount.m_id);   
        CleanupStack::PushL(entry);
    }
    else
    {
        emailAccounts->DefaultSmtpAccountL(iSmtpAccount);
        entry = iSession->GetEntryL(iSmtpAccount.iSmtpService); 
        CleanupStack::PushL(entry);
    }
    
    TMsvId outboxId = KMsvGlobalOutBoxIndexEntryId;
    
    // Create Childrenselection
    TMsvSelectionOrdering order;
    order.SetShowInvisibleEntries(ETrue);
    entry->SetSortTypeL(order);
    
    entry->SetEntryL(outboxId);
    // Get the  selection containing the IDs of all the context children
    CMsvEntrySelection* selection = entry->ChildrenL();
    
    // Fetch the Id of the first entry
    TMsvId entryId = KMsvNullIndexEntryId;
    entryId = (*selection)[0];
    
    delete selection;
    
    CMsvOperationWait* waiter = CMsvOperationWait::NewLC();
    CMsvOperation* emailOperation = entry->CopyL(entryId, iSmtpAccount.iSmtpService, waiter->iStatus);
    waiter->Start();
    CActiveScheduler::Start();
    CleanupStack::PushL(emailOperation);

    
    CleanupStack::PopAndDestroy(4, emailAccounts); // emailOperation, waiter, selection, emailAccounts
    iError = waiter->iStatus.Int();
    User::LeaveIfError(iError);
}

bool XQMessagingPrivate::startReceiving(XQMessaging::MsgType msgType)
{
    if (!ipObserver) 
    {
        XQMessaging::Error error = initializeObserver(msgType);
        if (error != XQMessaging::NoError) 
        {
            return false;
        }
    }
    ipObserver->iMsgType = msgType;
    ipObserver->iListenForIncomingMessages = true;

    return true;
}

void XQMessagingPrivate::stopReceiving()
{
    delete ipObserver;
    ipObserver = NULL;
}

XQMessaging::Error XQMessagingPrivate::initializeObserver(XQMessaging::MsgType msgType)
{
    TRAPD(err, ipObserver = CMsvSessionObserver::NewL(this, msgType));
    if (err) 
    {
        return XQMessaging::InternalError;
    }

    return XQMessaging::NoError;
}

void XQMessagingPrivate::DeliverMessage(XQMessage& message)
{
    emit ipParent->messageReceived(message);
}

void XQMessagingPrivate::DeliverError(XQMessaging::Error error)
{
    emit ipParent->error(error);
}

CMsvSessionObserver* CMsvSessionObserver::NewL(XQMessagingPrivate* apParent, XQMessaging::MsgType msgType)
{
    CMsvSessionObserver* self = new (ELeave) CMsvSessionObserver(apParent);
    self->ConstructL(msgType);
    return self;
}

CMsvSessionObserver::CMsvSessionObserver(XQMessagingPrivate* apParent)
    : CActive(EPriorityStandard), ipParent(apParent)
{
}

void CMsvSessionObserver::ConstructL(XQMessaging::MsgType msgType)
{
    iMsgType = msgType;
    ipReceivedMessages = new (ELeave) CMsvEntrySelection;
    // Initialize a channel of communication between a client thread (Client-side MTM,
    // User Interface MTM,or message client application) and the Message Server thread.
    ipMsvSession = CMsvSession::OpenAsyncL(*this);
    User::LeaveIfError(iTimer.CreateLocal());
    CActiveScheduler::Add(this);
    
    RFs fileServer;
    User::LeaveIfError(fileServer.Connect());
    CleanupClosePushL(fileServer);
    TBuf<KMaxPath> privatePath;
    fileServer.CreatePrivatePath(EDriveC);
    fileServer.PrivatePath(privatePath);
    iPath.Append(_L("c:"));
    iPath.Append(privatePath);
    iPath.Append(_L("tempattachments\\"));                         
    CFileMan* pFileMan = CFileMan::NewL(fileServer);
    CleanupStack::PushL(pFileMan);
    pFileMan->RmDir(iPath);
    fileServer.MkDirAll(iPath);
    CleanupStack::PopAndDestroy(pFileMan);
    CleanupStack::PopAndDestroy(&fileServer);
    
    ipClientMtmReg = CClientMtmRegistry::NewL(*ipMsvSession);
    //Note: If capabilities are missing, then iSmsMtm stays null
    // Get the SMS Mtm client from the registry
    ipSmsMtm = static_cast<CSmsClientMtm*>(ipClientMtmReg->NewMtmL(KUidMsgTypeSMS));
    ipMmsMtm = static_cast<CMmsClientMtm*>(ipClientMtmReg->NewMtmL(KUidMsgTypeMultimedia));
}

CMsvSessionObserver::~CMsvSessionObserver()
{
    TRAPD(error,
        RFs fileServer;
        if (fileServer.Connect() == KErrNone) 
        {
            CleanupClosePushL(fileServer);
            TBuf<KMaxPath> privatePath;
            fileServer.CreatePrivatePath(EDriveC);
            fileServer.PrivatePath(privatePath);
            TBuf<KMaxPath> path;
            path.Append(_L("c:"));
            path.Append(privatePath);
            path.Append(_L("tempattachments\\"));                         
            CFileMan* pFileMan=CFileMan::NewL(fileServer);
            CleanupStack::PushL(pFileMan);
            pFileMan->RmDir(path);
            CleanupStack::PopAndDestroy(pFileMan);
            CleanupStack::PopAndDestroy(&fileServer);
        }
    );

    Cancel();
    iTimer.Close();

    delete ipReceivedMessages;

    delete ipRichText;
    delete ipParaFormatLayer;
    delete ipClientMtmReg;

    //TODO: Check: ipMsvSession->RemoveObserver(*this);
    delete ipMsvSession;
}

void CMsvSessionObserver::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1,
                                              TAny* aArg2, TAny* /*aArg3*/)
{
    switch (aEvent) 
    {
        case EMsvServerReady:
            iMsvSessionReady = ETrue;
            break;
        case EMsvEntriesCreated:
            if (aArg2 && *(static_cast<TMsvId*>(aArg2)) == KObservedFolderId
                      && iListenForIncomingMessages) 
            {
                CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>(aArg1);

                if (entries != NULL) 
                {
                    TInt count = entries->Count();
                    while (count--) 
                    {
                        TRAPD(err,
                            const TMsvId id = (*entries)[count];
                            CMsvEntry* pReceivedEntry = ipMsvSession->GetEntryL(id);
                            CleanupStack::PushL(pReceivedEntry);
                            const TMsvEntry& entry = pReceivedEntry->Entry();
                            if ((iMsgType & XQMessaging::MsgTypeSMS) && 
                                (entry.iMtm == KUidMsgTypeSMS) &&
                                (entry.iType == KUidMsvMessageEntry)) 
                            {
                                ipReceivedMessages->AppendL(id);
                            } 
                            else if ((iMsgType & XQMessaging::MsgTypeMMS) &&
                                       (entry.iMtm == KUidMsgTypeMultimedia) &&
                                       (entry.iType == KUidMsvMessageEntry)) 
                            {
                                  ipReceivedMessages->AppendL(id);
                            }
                            CleanupStack::PopAndDestroy(pReceivedEntry);
                        );
                        if (err) 
                        {
                            ipParent->DeliverError(XQMessaging::InternalError);
                        }
                    }

                    if (ipReceivedMessages->Count() != 0) 
                    {
                        counter = 0;
                        Cancel(); // Cancel possible previous iTimer
                        // Wait 0.1 seconds to make sure that message is ready to be read
                        iTimer.After(iStatus, KWaitAfterReceivedMessage);
                        SetActive();
                    }
                }
            }
            break;

        default:
            break;
    }
}

void CMsvSessionObserver::RunL()
{
    TRAPD(err, DeliverMessagesL());
    if (err) 
    {
        counter++;
        // Wait another 0.1 seconds to give time to message to be ready
        iTimer.After(iStatus, KWaitAfterReceivedMessage);
        SetActive();
        if (counter > 50)
        { // One message is waited only for 5 seconds in maximum
            ipParent->DeliverError(XQMessaging::InternalError);
            // Remove problematic message from queue
            counter = 0;
            ipReceivedMessages->Delete(0,1);
            iTimer.After(iStatus, KWaitAfterReceivedMessage);
            SetActive();
        }
    }
}

void CMsvSessionObserver::DeliverMessagesL()
{
    TInt count = ipReceivedMessages->Count();
    while (count--) 
    {
        QString messageSubject;
        QString messageBody;
        QString messageSender;
        QStringList attachmentPaths;
        XQMessaging::MsgType type = XQMessaging::MsgTypeNotDefined;

        const TMsvId id = (*ipReceivedMessages)[0];
        CMsvEntry* pReceivedEntry = ipMsvSession->GetEntryL(id);
        CleanupStack::PushL(pReceivedEntry);

        // Read message sender
        if (ipSmsMtm || ipMmsMtm) 
        {
            if (ipSmsMtm && pReceivedEntry->Entry().iMtm == KUidMsgTypeSMS) 
            {
                ipSmsMtm->SwitchCurrentEntryL(id);
                ipSmsMtm->LoadMessageL();
                CSmsHeader& header = ipSmsMtm->SmsHeader();
                messageSender = QString::fromUtf16(header.FromAddress().Ptr(),
                                                   header.FromAddress().Length());
            } 
            else if (ipMmsMtm && pReceivedEntry->Entry().iMtm == KUidMsgTypeMultimedia) 
            {
                ipMmsMtm->SwitchCurrentEntryL(id);
                ipMmsMtm->LoadMessageL();
                messageSender = QString::fromUtf16(ipMmsMtm->Sender().Ptr(),
                                                   ipMmsMtm->Sender().Length());
            }
        } 
        else if (pReceivedEntry->Entry().iDetails.Length() > 0) 
        {
            messageSender = QString::fromUtf16(pReceivedEntry->Entry().iDetails.Ptr(),
                                               pReceivedEntry->Entry().iDetails.Length());
        }
        
        CMsvStore* pStore = pReceivedEntry->ReadStoreL();
        CleanupStack::PushL(pStore);
        if (pReceivedEntry->Entry().iMtm == KUidMsgTypeSMS) 
        {
            type = XQMessaging::MsgTypeSMS;
            // Read message body for SMS
            if (pStore->HasBodyTextL()) 
            {
                if (!ipRichText) 
                {
                    ipCharFormatLayer = CCharFormatLayer::NewL();
                    ipParaFormatLayer = CParaFormatLayer::NewL();
                    ipRichText=CRichText::NewL(ipParaFormatLayer,ipCharFormatLayer);
                }
                ipRichText->Reset();
                pStore->RestoreBodyTextL(*ipRichText);
                HBufC* pMessage = HBufC::NewLC(ipRichText->DocumentLength());
                TPtr ptr2(pMessage->Des());
                ipRichText->Extract(ptr2);
                messageBody = QString::fromUtf16(pMessage->Ptr(),pMessage->Length());
                CleanupStack::PopAndDestroy(pMessage);
            }
        } 
        else if (pReceivedEntry->Entry().iMtm == KUidMsgTypeMultimedia) 
        {
            type = XQMessaging::MsgTypeMMS;
            // Read message subject for MMS
            if (pReceivedEntry->Entry().iDescription.Length() > 0) 
            {
                messageSubject = QString::fromUtf16(pReceivedEntry->Entry().iDescription.Ptr(),
                                                    pReceivedEntry->Entry().iDescription.Length());
            }
            TInt count = pStore->AttachmentManagerL().AttachmentCount();
            TBool textAdded = EFalse;
            for (TInt i = 0; i < count; i++) 
            {
                CMsvAttachment* pAttachment = pStore->AttachmentManagerL().GetAttachmentInfoL(i);
                CleanupStack::PushL(pAttachment);
                if (pAttachment->MimeType() == _L8("text/plain") && !textAdded) 
                {
                    // Read message body for MMS
                    textAdded = ETrue;
                    RFile file = pStore->AttachmentManagerL().GetAttachmentFileL(i);
                    CleanupClosePushL(file);
                    TInt fileSize;
                    file.Size(fileSize);
                    HBufC8* pFileContent = HBufC8::NewLC(fileSize);
                    TPtr8 fileContent(pFileContent->Des());
                    file.Read(fileContent);
                    HBufC* pMsg = CnvUtfConverter::ConvertToUnicodeFromUtf8L(*pFileContent);
                    CleanupStack::PopAndDestroy(pFileContent);
                    CleanupStack::PopAndDestroy(&file);
                    messageBody = QString::fromUtf16(pMsg->Ptr(), pMsg->Length());
                    delete pMsg;
                }
                else 
                {
                    // Read attachment for MMS
                    //const TDesC& filePath = pAttachment->FilePath();
                    //attachmentPaths.append(QString::fromUtf16(filePath.Ptr(),filePath.Length()));
                    // Read attachment for MMS
                    RFile file = pStore->AttachmentManagerL().GetAttachmentFileL(i);
                    CleanupClosePushL(file);
                    TInt fileSize;
                    file.Size(fileSize);
                    HBufC8* pFileContent = HBufC8::NewL(fileSize);
                    TPtr8 fileContent(pFileContent->Des());
                    file.Read(fileContent);
                    CleanupStack::PopAndDestroy(&file);
                    CleanupStack::PushL(pFileContent);
                    // write tempFile to private folder
                    RFs fileServer;
                    User::LeaveIfError(fileServer.Connect());
                    CleanupClosePushL(fileServer);
                    RFile file2;
                    TFileName tempFileName;
                    TInt err = file2.Temp(fileServer,iPath,tempFileName,EFileWrite);
                    if (err == KErrNone) 
                    {
                         CleanupClosePushL(file2);
                         file2.Write(*pFileContent);
                         CleanupStack::PopAndDestroy(&file2);
                         attachmentPaths.append(QString::fromUtf16(tempFileName.Ptr(),tempFileName.Length()));
                    }
                    CleanupStack::PopAndDestroy(&fileServer);
                    CleanupStack::PopAndDestroy(pFileContent);
                }
                CleanupStack::PopAndDestroy(pAttachment);
            }
        }
        CleanupStack::PopAndDestroy(pStore);

        CleanupStack::PopAndDestroy(pReceivedEntry);
        ipReceivedMessages->Delete(0,1);

        XQMessage message;
        message.setType(type);
        message.setSender(messageSender);
        if (!messageBody.isEmpty()) 
        {
            message.setBody(messageBody);
        }
        if (!messageSubject.isEmpty()) 
        {
            message.setSubject(messageSubject);
        }
        if (!attachmentPaths.isEmpty()) 
        {
            message.setAttachments(attachmentPaths);
        }
        ipParent->DeliverMessage(message);
    }
}

void CMsvSessionObserver::DoCancel()
{
    iTimer.Cancel();
}

XQMessaging::Error XQMessagingPrivate::error() const
{
    switch (iError) 
    {
        case KErrNone: 
            return XQMessaging::NoError;
        case KErrNoMemory: 
            return XQMessaging::OutOfMemoryError;
        case XQMessaging::NullMessageBodyError:
            return XQMessaging::NullMessageBodyError;
        case XQMessaging::ReceiverNotDefinedError:
            return XQMessaging::ReceiverNotDefinedError;
        case XQMessaging::InternalError:
            return XQMessaging::InternalError;
        case XQMessaging::NoAccountError:
            return XQMessaging::NoAccountError;
        default: 
            return XQMessaging::UnknownError;
    }    
}

// End of file
