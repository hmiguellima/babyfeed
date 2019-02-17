import QtQuick 1.1
import com.nokia.extras 1.1
import com.nokia.symbian 1.1

Page {
    id: checkInOutScreen
    objectName: "checkInOutScreen"
    tools: toolbar
    orientationLock: PageOrientation.LockPortrait

    signal canceled();
    signal startStopClicked();
    signal leftFeedClicked();
    signal bottleClicked();
    signal rightFeedClicked();
    signal endFeeds();

    property alias pageTitleText: title.title
    property alias parcialTimerText: parcialTimeTimerLbl.text
    property alias totalTimerText: totalTimeTimerLbl.text

    Image {
        anchors.fill: parent
        fillMode: Image.Stretch
        source: "qrc:/resources/resources/main_screen_bgr.png"
        smooth: true
    }

    PageTitle {
        id: title
        anchors.top: parent.top
        title: "<b>BabyFeed</b> - Cronometer"
        fontSize: styles.textHeadingSize
    }

    Image {
        id: stopWatchImage
        anchors.centerIn: parent
        width: 330
        fillMode: Image.PreserveAspectFit
        source: "qrc:/resources/resources/stopwatch.png"
    }

    ToolButton {
        id: startStop
        text: qsTr("Start/Stop")
        anchors.bottom: stopWatchImage.bottom
        anchors.bottomMargin: 15
        anchors.horizontalCenter: stopWatchImage.horizontalCenter
        onClicked: handleStartStop();
    }

    Label {
        id: parcialTimeTimerLbl
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -35
        font.pixelSize: styles.timerBigSizePx
        text: "00:00"
    }

    Label {
        id: totalTimeTimerLbl
        anchors.top: parcialTimeTimerLbl.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parcialTimeTimerLbl.horizontalCenter
        font.pixelSize: styles.timerSmallSizePx
        text: "00:00"
        visible: false
    }

    ToolBar {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 70
        id: eventsBar

        tools: ToolBarLayout {
            ButtonRow {
                id: eventTypeBtnRow
                checkedButton: leftFeedBtn
                anchors.fill: parent
                height: 70

                EventButton {
                    id: leftFeedBtn
                    iconSource: "qrc:/icons/icons/breastfeeding-left.png"
                    height: 70
                    onClicked: checkInOutScreen.leftFeedClicked();
                }

                EventButton {
                    id: bottleFeedBtn
                    iconSource: "qrc:/icons/icons/baby_bottle.png"
                    height: 70
                    onClicked: checkInOutScreen.bottleClicked();
                }

                EventButton {
                    id: rightFeedbtn
                    iconSource: "qrc:/icons/icons/breastfeeding-right.png"
                    height: 70
                    onClicked: checkInOutScreen.rightFeedClicked();
                }
            }
        }
    }

    ToolBarLayout {
        id: toolbar
        visible: true

        ToolButton {
            id: backBtn
            iconSource: "toolbar-back"
            onClicked: checkInOutScreen.canceled();
        }
    }

    QueryDialog {
        id: confirmEndEventsDlg
        titleText: qsTr("Please confirm")
        acceptButtonText: qsTr("Yes")
        rejectButtonText: qsTr("No")
        message: qsTr("Stop feeding?")
        height: 1

        onRejected: backBtn.enabled=true;
        onAccepted: checkInOutScreen.endFeeds();
    }

    function handleStartStop() {
        backBtn.enabled = false;
        eventTypeBtnRow.enabled=!eventTypeBtnRow.enabled;
        checkInOutScreen.startStopClicked();
        if (eventTypeBtnRow.enabled) {
            totalTimeTimerLbl.visible = true;
            confirmEndEventsDlg.open();
        }
    }
}
