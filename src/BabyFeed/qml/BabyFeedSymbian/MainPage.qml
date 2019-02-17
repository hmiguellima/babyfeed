import QtQuick 1.1
import com.nokia.extras 1.1
import com.nokia.symbian 1.1

Page {
    id: mainScreen
    objectName: "mainScreen"
    tools: toolbar
    orientationLock: PageOrientation.LockPortrait

    signal babyIndexChanged(int index)
    signal editBabyClicked(int index)
    signal deleteBabyClicked(int index)
    signal prevDateClicked()
    signal nextDateClicked()
    signal dateChanged(int year, int month, int day)
    signal checkEventClicked(int index)
    signal uncheckEventClicked(int index)
    signal editEventClicked(int index)
    signal deleteEventClicked(int index)
    signal timerEventClicked();
    signal manualEventClicked();
    signal reportClicked();
    signal newBabyClicked();

    property alias setDateBtnText: setDateBtn.text
    property alias pageTitleText: title.title
    property alias currentBabyIndex: babies.currentBabyIndex

    Image {
        anchors.fill: parent
        fillMode: Image.Stretch
        source: "qrc:/resources/resources/main_screen_bgr.png"
        smooth: true
    }

    PageTitle {
        id: title
        anchors.top: parent.top
        title: "<b>BabyFeed</b> - History"
    }

    BabyPages {
        id: babies
        anchors.top: title.bottom
        model: babiesModel
    }

    Item {
        id: dateButtons
        width: parent.width
        anchors.top: babies.bottom
        anchors.topMargin: 2
        height: 60

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.3; color: "#b6ddc7" }
                GradientStop { position: 1.0; color: "#ecbabd" }
            }
        }


        ToolButton {
            id: prevDateBtn
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 60
            text: "<"
            platformInverted: true
            onClicked: prevDateClicked();
        }
        ToolButton {
           id: setDateBtn
           anchors.left: prevDateBtn.right
           anchors.right: nextDateBtn.left
           anchors.verticalCenter: parent.verticalCenter
           text: "Thu, Nov/03/2011"
           platformInverted: true
           onClicked: showDateDialog();
        }
        ToolButton {
           id: nextDateBtn
           anchors.right: parent.right
           anchors.rightMargin: 5
           anchors.verticalCenter: parent.verticalCenter
           width: 60
           text: ">"
           platformInverted: true
           onClicked: nextDateClicked()
        }
    }

    Component {
        id: eventRecord

        Rectangle {
            width: eventsView.width
            height: 65
            Row {
                anchors.fill: parent
                spacing: styles.defaultSpacing

                Image {
                    source: icon
                }

                Text {
                    text: desc
                    height: parent.height
                    width: parent.width
                    font.pointSize: styles.textHeadingSize
                    verticalAlignment: "AlignVCenter"
                    horizontalAlignment: (empty===true?"AlignHCenter":"AlignLeft")
                }
            }

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: "#E0E0E0"
            }

            Text {
                anchors.right: parent.right
                height: parent.height
                verticalAlignment: "AlignVCenter"
                anchors.rightMargin: 10
                text: ">"
                font.pointSize: styles.textTitleSize
                visible: (empty===true?false:true)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: menuItemClicked(index, checked, empty);
            }
        }
    }

    ListView {
        id: eventsView
        width: parent.width
        model: eventsModel
        anchors.top: dateButtons.bottom
        anchors.bottom: parent.bottom
        clip: true
        delegate: eventRecord
    }

    ListModel {
        id: babySampleModel

        ListElement {
            name: "Barbara"
            age: "10 Months"
            photo: "qrc:/icons/icons/baby_girl_icon.png"
            measures: "Sample measures 1"
        }

        ListElement {
            name: "Clara"
            age: "2 Months"
            photo: "qrc:/icons/icons/baby_boy_icon.png"
            measures: "Sample measures 1"
        }
    }


    ListModel {
        id: eventsSampleModel

        ListElement {
            icon: "qrc:/icons/icons/nappy_checked.png"
            desc: "End: 01:49, Min: 0"
        }

        ListElement {
            icon: "qrc:/icons/icons/breastfeeding-left_checked.png"
            desc: "End: 01:49, Min: 0"
        }

    }

    ToolBarLayout {
        id: toolbar
        visible: true

        Row {
            anchors.left: parent.left
            anchors.right: menuBtn.left
            anchors.leftMargin: 10
            spacing: 14

            MyToolButton {
                iconSource: "qrc:/icons/icons/close-symbian.svg"
                onClicked: Qt.quit();
            }

            MyToolButton {
                id: cronoBtn
                iconSource: "qrc:/icons/icons/timer-symbian.svg"
                onClicked: timerEventClicked();
            }

            MyToolButton {
                id: customBtn
                iconSource: "qrc:/icons/icons/accessories-text-editor-symbian.svg"
                onClicked: manualEventClicked();
            }

            MyToolButton {
                id: reportsBtn
                iconSource: "qrc:/icons/icons/x-office-spreadsheet-symbian.svg"
                onClicked: reportClicked();
            }

        }

        ToolButton {
            id: menuBtn
            iconSource: "toolbar-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status == DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }

    DatePickerDialog {
        id: dateDlg
        titleText: qsTr("Enter date")
        acceptButtonText: qsTr("OK")
        rejectButtonText: qsTr("Cancel")
        minimumYear: 2000
        onAccepted: handleDatePickerSelection()
    }

    Menu {
         id: eventCheckedMenu
         property int eventIndex: 0
         MenuLayout {
             MenuItem {text: qsTr("Uncheck"); onClicked: uncheckEventClicked(eventCheckedMenu.eventIndex);}
             MenuItem {text: qsTr("Edit"); onClicked: editEventClicked(eventCheckedMenu.eventIndex);}
             MenuItem {text: qsTr("Delete"); onClicked: handleDeleteEventClicked(eventCheckedMenu.eventIndex);}
         }
    }

    Menu {
         id: eventUncheckedMenu
         property int eventIndex: 0
         MenuLayout {
             MenuItem {text: qsTr("Check"); onClicked: checkEventClicked(eventUncheckedMenu.eventIndex);}
             MenuItem {text: qsTr("Edit"); onClicked: editEventClicked(eventUncheckedMenu.eventIndex);}
             MenuItem {text: qsTr("Delete"); onClicked: handleDeleteEventClicked(eventUncheckedMenu.eventIndex);}
         }
    }

    QueryDialog {
        id: confirmDeleteRecordDlg
        titleText: qsTr("Please confirm")
        acceptButtonText: qsTr("Delete")
        rejectButtonText: qsTr("Cancel")
        message: qsTr("Remove record?")
        height: 1

        property int eventIndex: 0

        onAccepted: deleteEventClicked(eventIndex);
    }

    function showDateDialog() {
        var d = new Date();
        dateDlg.year = d.getFullYear();
        dateDlg.month = d.getMonth()+1;
        dateDlg.day = d.getDate();
        dateDlg.open();
    }

    function handleDatePickerSelection() {
        dateChanged(dateDlg.year, dateDlg.month, dateDlg.day);
    }

    function menuItemClicked(index, checked, empty) {
        console.debug("qml:menuItemClicked")
        if (!empty) {
            if (checked) {
                eventCheckedMenu.eventIndex=index;
                eventCheckedMenu.open();
            } else {
                eventUncheckedMenu.eventIndex=index;
                eventUncheckedMenu.open();
            }
        }
    }

    function handleDeleteEventClicked(eventIndex) {
        console.debug("qml:handleDeleteEventClicked");
        confirmDeleteRecordDlg.eventIndex=eventIndex;
        confirmDeleteRecordDlg.open();
    }

    function positionBabyToIndex(index) {
        babies.positionToIndex(index);
    }
}
