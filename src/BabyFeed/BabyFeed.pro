#CONFIG += debug

QT += core gui sql declarative
CONFIG += qt-components mobility
MOBILITY += contacts multimedia organizer messaging

TARGET = babyfeed
TEMPLATE = app
VERSION = 1.4.1

#DEFINES += MEEGO_VERSION
#CONFIG += meego_version
DEFINES += SYMBIAN_VERSION
DEFINES += TIME_TRIAL_VERSION
CONFIG += sym_version

# Add more folders to ship with the application, here
folder_01.source = qml/BabyFeedMeego
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
sym_version:CONFIG += qt-components

meego_version {
    INCLUDEPATH += /usr/include/mkcal
    INCLUDEPATH += /usr/include/kcalcoren

    #LIBS += -ldl /scratchbox/users/hlima/targets/HARMATTAN_X86/usr/lib/libmkcal.so
    #LIBS += -ldl /scratchbox/users/hlima/targets/HARMATTAN_X86/usr/lib/libkcalcoren.so
    LIBS += -ldl /scratchbox/users/hlima/targets/HARMATTAN_ARMEL/usr/lib/libmkcal.so
    LIBS += -ldl /scratchbox/users/hlima/targets/HARMATTAN_ARMEL/usr/lib/libkcalcoren.so
}

win32:INCLUDEPATH += C:/Libs/zlib/src/zlib/1.2.3/zlib-1.2.3
include( qwt.pri )

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    controller/screen.cpp \
    controller/manualeventscreen.cpp \
    controller/mainscreen.cpp \
    controller/checkinoutscreen.cpp \
    controller/babyscreen.cpp \
    model/rfeedingevent.cpp \
    model/pottyevent.cpp \
    model/notification.cpp \
    model/nobaby.cpp \
    model/medicineevent.cpp \
    model/measureevent.cpp \
    model/lfeedingevent.cpp \
    model/feedingevent.cpp \
    model/feedconfig.cpp \
    model/eventmodel.cpp \
    model/eventbus.cpp \
    model/event.cpp \
    model/emptyevent.cpp \
    model/contactsmodel.cpp \
    model/bfeedingevent.cpp \
    model/baby.cpp \
    view/view.cpp \
    view/mainview.cpp \
    global.cpp \
    mainwindow.cpp \
    quazip/zip.c \
    quazip/unzip.c \
    quazip/quazipnewinfo.cpp \
    quazip/quazipfile.cpp \
    quazip/quazip.cpp \
    quazip/quacrc32.cpp \
    quazip/quaadler32.cpp \
    quazip/JlCompress.cpp \
    quazip/ioapi.c \
    model/babiesmodel.cpp \
    view/manualeventview.cpp \
    view/babyview.cpp \
    view/checkinoutview.cpp \
    controller/reportscreen.cpp \
    view/reportsview.cpp \
    model/calwrapper.cpp \
    model/contactswrapper.cpp

meego_version {
    # Please do not modify the following two lines. Required for deployment.
    include(qmlapplicationviewer/qmlapplicationviewer.pri)
    qtcAddDeployment()

    RESOURCES += babyfeed_meego.qrc
}

sym_version {
    RESOURCES += babyfeed_symbian.qrc
}

HEADERS += \
    controller/screen.h \
    controller/manualeventscreen.h \
    controller/mainscreen.h \
    controller/checkinoutscreen.h \
    controller/babyscreen.h \
    model/rfeedingevent.h \
    model/pottyevent.h \
    model/notification.h \
    model/nobaby.h \
    model/medicineevent.h \
    model/measureevent.h \
    model/lfeedingevent.h \
    model/feedingevent.h \
    model/feedconfig.h \
    model/eventmodel.h \
    model/eventbus.h \
    model/event.h \
    model/emptyevent.h \
    model/contactsmodel.h \
    model/bfeedingevent.h \
    model/baby.h \
    view/view.h \
    view/mainview.h \
    global.h \
    mainwindow.h \
    quazip/zip.h \
    quazip/unzip.h \
    quazip/quazipnewinfo.h \
    quazip/quazipfileinfo.h \
    quazip/quazipfile.h \
    quazip/quazip.h \
    quazip/quacrc32.h \
    quazip/quachecksum32.h \
    quazip/quaadler32.h \
    quazip/JlCompress.h \
    quazip/ioapi.h \
    quazip/crypt.h \
    model/babiesmodel.h \
    view/manualeventview.h \
    view/babyview.h \
    view/checkinoutview.h \
    controller/reportscreen.h \
    view/reportsview.h \
    model/calwrapper.h \
    model/contactswrapper.h

meego_version {
    target.path = /opt/babyfeed/bin
    INSTALLS += target

    desktopfile.files = $${TARGET}.desktop
    desktopfile.path = /usr/share/applications
    INSTALLS += desktopfile

    #icon64.path = $$DATADIR/icons/hicolor/64x64/apps
    #icon64.files += babyfeed64.png
    #INSTALLS += icon64

    #icon80.path = $$DATADIR/icons/hicolor/80x80/apps
    #icon80.files += babyfeed80.png
    #INSTALLS += icon80
}

TRANSLATIONS = babyfeed_fr.ts \
               babyfeed_es.ts \
               babyfeed_pt.ts

symbian*:{
    #Dados para OVI
    #TARGET.UID3 = 0x20036D8E
    #DEPLOYMENT.installer_header=0x2002CCCF
    #vendorinfo = \
    #  "%{\"Hugo Miguel Barbarrica Rodrigues Lima\"}" \
    #  ":\"Hugo Miguel Barbarrica Rodrigues Lima\""
    #my_deployment.pkg_prerules += vendorinfo

    #Dados para self-signed
    TARGET.UID3 = 0xE4DE5D27
    DEPLOYMENT.installer_header=0xA000D7CE
    vendorinfo = \
      "%{\"CustomVendor-EN\"}" \
      ":\"CustomVendor\""
    my_deployment.pkg_prerules += vendorinfo

    ICON = icons/babyfeed_icon.svg

    INCLUDEPATH += C:/QtSDK/Symbian/SDKs/Symbian3Qt474/epoc32/include
    INCLUDEPATH += C:/QtSDK/Symbian/SDKs/Symbian3Qt474/epoc32/include/stdapis

    LIBS += -lestor -lefsrv
    LIBS += -lcone -leikcore -lavkon
    LIBS += -lsendas2 -lmsgs -letext -lcharconv -lgsmu -limcm -lbafl -lmtur

    TARGET.CAPABILITY += ReadUserData \
        WriteUserData \
        NetworkServices \
        LocalServices \
        UserEnvironment
    TARGET.EPOCHEAPSIZE = 0x400000 0x6000000
    TARGET.EPOCALLOWDLLDATA = 1

    supported_platforms = \
         "; S60 5.0 and Symbian^3" \
         "[0x1028315F],0,0,0,{\"S60ProductID\"}" \
         "[0x20022E6D],0,0,0,{\"S60ProductID\"}" \
         "; S60 3.1 and S60 3.2" \
         "[0x102032BE],0,0,0,{\"S60ProductID\"}" \
         "[0x102752AE],0,0,0,{\"S60ProductID\"}"

    default_deployment.pkg_prerules -= pkg_platform_dependencies
    my_deployment.pkg_prerules += supported_platforms

    DEPLOYMENT += my_deployment
}

OTHER_FILES += \
    qml/BabyFeedMeego/BabyPage.qml \
    qml/BabyFeedMeego/CheckInOutPage.qml \
    qml/BabyFeedMeego/ReportsPage.qml \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qml/BabyFeedSymbian/Styles.qml \
    qml/BabyFeedSymbian/Splash.qml \
    qml/BabyFeedSymbian/ReportsPage.qml \
    qml/BabyFeedSymbian/PageTitle.qml \
    qml/BabyFeedSymbian/ManualEventPage.qml \
    qml/BabyFeedSymbian/MainPage.qml \
    qml/BabyFeedSymbian/Main.qml \
    qml/BabyFeedSymbian/CheckInOutPage.qml \
    qml/BabyFeedSymbian/BabyPages.qml \
    qml/BabyFeedSymbian/BabyPage.qml \
    qml/BabyFeedSymbian/MyToolButton.qml \
    qml/BabyFeedSymbian/EventButton.qml \
    qml/BabyFeedMeego/Styles.qml \
    qml/BabyFeedMeego/Splash.qml \
    qml/BabyFeedMeego/PageTitle.qml \
    qml/BabyFeedMeego/ManualEventPage.qml \
    qml/BabyFeedMeego/MainPage.qml \
    qml/BabyFeedMeego/Main.qml \
    qml/BabyFeedMeego/BabyPages.qml
