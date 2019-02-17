import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: Splash {
        image : "qrc:/resources/resources/splash.svg"
        timeout: 2000
        fadeout: 700
        Component.onCompleted: activate();
        onFinished: onSplashFinished();
    }

    signal splashFinished()
    signal screenLoaded()
    signal aboutClicked()
    signal backupClicked()
    signal restoreClicked()
    signal helpClicked()

    Styles {
        id: styles
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("About"); onClicked: aboutClicked(); }
            //MenuItem { text: qsTr("Backup"); onClicked: backupClicked(); }
            //MenuItem { text: qsTr("Restore"); onClicked: restoreClicked(); }
            MenuItem { text: qsTr("Help"); onClicked: helpClicked(); }
        }
    }

    QueryDialog {
        id: messageBox
        acceptButtonText: qsTr("Ok");
        rejectButtonText: ""
        titleText: "BabyFeed"
    }


    Rectangle {
        id: busyBox
        anchors.fill: parent
        color: "#FFFFFF"
        opacity: 0.7
        visible: false

        BusyIndicator {
            id: busyIndicator
            anchors.centerIn: parent
            opacity: 1

            platformStyle: BusyIndicatorStyle { size: "large" }
            running:  false
        }
    }

    function showBusyBox() {
        busyIndicator.running=true;
        busyBox.visible=true;
    }

    function hideBusyBox() {
        busyIndicator.running=false;
        busyBox.visible=false;
    }

    function onSplashFinished() {
        console.debug("qml:splashFinished");
        appWindow.splashFinished();
    }

    function showScreen(url) {
        console.debug("qml:showScreen:"+url);
        appWindow.pageStack.replace(url)
        appWindow.screenLoaded();
    }

    function showMessageBox(message) {
        messageBox.message=message;
        messageBox.open();
    }
}
