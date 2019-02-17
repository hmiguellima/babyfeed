#-------------------------------------------------
#
# Project created by QtCreator 2010-08-16T00:18:09
#
#-------------------------------------------------

CONFIG += debug

QT += core gui sql

TARGET = BabyFeed
TEMPLATE = app

DEFINES += XQCAMERA_NO_LIBRARY
DEFINES += XQMESSAGING_NO_LIBRARY
INCLUDEPATH += D:/S60/devices/S60_5th_Edition_SDK_v1.0/epoc32/include
#INCLUDEPATH += D:/NokiaQtSDK/Symbian/SDK/epoc32/include

include( qwt.pri )

SOURCES += main.cpp \
    mainwindow.cpp \
    mainscreen.cpp \
    event.cpp \
    checkinoutscreen.cpp \
    optionsscreen.cpp \
    screen.cpp \
    eventmodel.cpp \
    manualeventscreen.cpp \
    babyicon.cpp \
    baby.cpp \
    nobaby.cpp \
    emptyevent.cpp \
    babyscreen.cpp \
    kineticscrollarea.cpp \
    expandedlistview.cpp \
    eventbus.cpp \
    camerascreen.cpp \
    flickable/qscrollareakineticscroller.cpp \
    flickable/qkineticscroller.cpp \
    eventtypepanel.cpp \
    notification.cpp \
    feedconfig.cpp \
    calendarwidget.cpp \
    contactsmodel.cpp \
    labelbar.cpp \
    reportscreen.cpp \
    feedingevent.cpp \
    medicineevent.cpp

HEADERS  += \
    mainwindow.h \
    mainscreen.h \
    event.h \
    checkinoutscreen.h \
    optionsscreen.h \
    screen.h \
    eventmodel.h \
    manualeventscreen.h \
    babyicon.h \
    baby.h \
    nobaby.h \
    emptyevent.h \
    babyscreen.h \
    kineticscrollarea.h \
    expandedlistview.h \
    eventbus.h \
    camerascreen.h \
    flickable/qkineticscroller_p.h \
    flickable/qkineticscroller.h \
    flickable/qscrollareakineticscroller.h \
    eventtypepanel.h \
    notification.h \
    feedconfig.h \
    calendarwidget.h \
    contactsmodel.h \
    labelbar.h \
    reportscreen.h \
    feedingevent.h \
    medicineevent.h

FORMS    += \
    checkinoutscreen.ui \
    mainscreen.ui \
    optionsscreen.ui \
    mainwindow.ui \
    manualeventscreen.ui \
    babyicon.ui \
    babyscreen.ui \
    camerascreen.ui \
    calendarwidget.ui

symbian*:{
    LIBS += -lcamerawrapper -lfbscli
    LIBS += -lalarmclient -lalarmshared
    LIBS += -lcntmodel -lbafl -lefsrv -lestor -lexiflib.dll
    LIBS += -lcone -leikcore -lavkon
    LIBS += -lhwrmvibraclient
    #LIBS += -lsendas2 -lmsgs -letext -lefsrv -lcharconv -lgsmu -limcm -lbafl -lmtur

    SOURCES += alarms/xqalarms_p.cpp \
        alarms/xqalarms.cpp \
        camera/xqviewfinderwidget_p.cpp \
        camera/xqviewfinderwidget.cpp \
        camera/xqcamera_p.cpp \
        camera/xqcamera.cpp \
        contacts/xqcontacts.cpp \
        contacts/xqcontact.cpp \
        contacts/xqcontacts_s60_p.cpp \
        vibra/xqvibra_p.cpp \
        vibra/xqvibra.cpp
        #messaging/xqmessaging_s60_p.cpp \
        #messaging/xqmessaging.cpp


    HEADERS += alarms/xqalarms.h \
        alarms/alarms_global.h \
        alarms/xqalarms_p.h \
        camera/xqviewfinderwidget.h \
        camera/xqcamera_p.h \
        camera/xqcamera.h \
        camera/camera_global.h \
        camera/xqviewfinderwidget_p.h \
        contacts/xqcontacts.h \
        contacts/xqcontact_p.h \
        contacts/xqcontact.h \
        contacts/contacts_global.h \
        contacts/xqcontacts_s60_p.h \
        vibra/xqvibra_p.h \
        vibra/xqvibra.h \
        vibra/vibra_global.h
        #messaging/xqmessaging_s60_p.h \
        #messaging/xqmessaging.h \
        #messaging/messaging_global.h

    TARGET.CAPABILITY += ReadUserData \
        WriteUserData \
        NetworkServices \
        LocalServices \
        UserEnvironment
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x1000000
    TARGET.EPOCALLOWDLLDATA = 1
}

RESOURCES += \
    babyfeed.qrc

OTHER_FILES += \
    qwt.pri
