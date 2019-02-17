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
    signal langClicked(string lang)
    signal exportClicked(string email)

    Styles {
        id: styles
    }

    Menu {
        id: langMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: "English"; onClicked: langClicked("en"); }
            MenuItem { text: "Français"; onClicked: langClicked("fr"); }
            MenuItem { text: "Español"; onClicked: langClicked("es"); }
            MenuItem { text: "Português"; onClicked: langClicked("pt"); }
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("About"); onClicked: aboutClicked(); }
            /*MenuItem { text: qsTr("Backup"); onClicked: backupClicked(); }
            MenuItem { text: qsTr("Restore"); onClicked: restoreClicked(); }*/
            MenuItem { text: qsTr("Export Events"); onClicked: exportDialog.open(); }
            MenuItem { text: qsTr("Language"); onClicked: langMenu.open(); }
            MenuItem { text: qsTr("Help"); onClicked: helpClicked(); }
        }
    }

    Dialog {
        id: exportDialog

        content: Item {
            width: parent.width
            height:200

            Column {
                spacing: 10

                Label {
                    text: qsTr("Export Events")
                    color: "#ffffff"
                    font.pointSize: styles.textHeadingSize
                    width: 320
                    horizontalAlignment: "AlignHCenter"
                }

                Label {
                    text: qsTr("Destination email:")
                    color: "#ffffff"
                }
                TextField {
                    id: exportEmail
                    validator: RegExpValidator {
                        regExp: /^([a-zA-Z0-9_\.\-])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9]{2,4})+$/
                    }

                    width: 320
                }
            }
        }

        buttons: Button {
            text: qsTr("Send")
            onClicked: handleSend();
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

    function handleSend() {
        exportDialog.accept();
        if (!exportEmail.acceptableInput)
            showMessageBox(qsTr("Invalid destination email"));
        else
            exportClicked(exportEmail.text);
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
