import QtQuick 1.1
import com.nokia.extras 1.1
import com.nokia.symbian 1.1

Page {
    id: manualEventScreen
    objectName: "manualEventScreen"
    tools: toolbar
    orientationLock: PageOrientation.LockPortrait

    signal canceled()
    signal save()

    property int eventTypeIndex: 0
    property alias startDateDay: startDateDlg.day
    property alias startDateMonth: startDateDlg.month
    property alias startDateYear: startDateDlg.year
    property alias endDateDay: endDateDlg.day
    property alias endDateMonth: endDateDlg.month
    property alias endDateYear: endDateDlg.year
    property alias startTimeHour: startTimeDlg.hour
    property alias startTimeMinute: startTimeDlg.minute
    property alias duration: durationField.text
    property alias generalNotes: genericNotesEdit.text
    property alias medicineName: medicineNameField.text
    property alias medicineNotes: medicineNotesEdit.text
    property alias mWeight: weightEdit.text
    property alias mHeight: heightEdit.text
    property alias mCephalic: cephalicEdit.text
    property alias interval: intervalField.text
    property alias startDateEnabled: startDateBtn.enabled
    property alias startTimeEnabled: timeBtn.enabled
    property alias eventTypeBtnRowEnabled: eventTypeBtnRow.enabled
    property alias recurrenceVisible: recurrenceTabBtn.enabled
    property alias pageTitleText: title.title
    property int textFieldWidth: 320

    Image {
        anchors.fill: parent
        fillMode: Image.Stretch
        source: "qrc:/resources/resources/main_screen_bgr.png"
        smooth: true
    }

    PageTitle {
        id: title
        anchors.top: parent.top
        title: "BabyFeed - Edit record"
    }

    Flickable {
        id: scrollArea
        anchors.fill: parent
        anchors.topMargin: 62
        contentHeight: 496
        clip: true

        TabBarLayout  {
             id: tabsToolBar
             anchors.top: parent.top
             anchors.topMargin: 0
             anchors.left: parent.left
             anchors.right: parent.right
             height: 50

             TabButton { id:whenTabBtn; tab: whenTab; text: qsTr("When?") }
             TabButton { id:notesTabBtn; tab: notesTab; text: qsTr("Notes") }
             TabButton { id:recurrenceTabBtn; tab: recurrenceTab; text: qsTr("Recurrence") }
        }

        TabGroup {
              id: tabGroup
              anchors.top: tabsToolBar.bottom
              anchors.left: parent.left
              anchors.right: parent.right
              anchors.bottom: eventsBar.top
              anchors.margins: styles.defaultSpacing

              currentTab: whenTab

              Page {
                  id: whenTab

                  Item {
                      anchors.fill: parent
                      anchors.margins: styles.defaultSpacing

                      Column {
                          spacing: styles.defaultSpacing

                          Row {
                              spacing: styles.defaultSpacing

                              Label {
                                  height: parent.height
                                  verticalAlignment: "AlignVCenter"
                                  color: styles.defaultLabelTextColor
                                  text: qsTr("Date:")
                              }

                              ToolButton {
                                  id: startDateBtn
                                  platformInverted: true
                                  width: 240
                                  text: getDateText(startDateYear, startDateMonth, startDateDay)
                                  onClicked: startDateDlg.open();
                              }
                          }

                          Row {
                              spacing: styles.defaultSpacing

                              Label {
                                  height: parent.height
                                  color: styles.defaultLabelTextColor
                                  verticalAlignment: "AlignVCenter"
                                  text: qsTr("Time:")
                              }

                              ToolButton {
                                  id: timeBtn
                                  width: 120
                                  platformInverted: true
                                  text: getTimeText(startTimeHour, startTimeMinute)
                                  onClicked: startTimeDlg.open();
                              }
                          }

                          Row {
                              spacing: styles.defaultSpacing

                              Label {
                                  height: parent.height
                                  color: styles.defaultLabelTextColor
                                  verticalAlignment: "AlignVCenter"
                                  text: qsTr("Duration (Min):")
                              }

                              TextField {
                                  id: durationField
                                  width: 80
                                  text: "0"
                                  validator: IntValidator{bottom: 0; top: 59;}
                              }
                          }
                      }
                  }

              }

              // Notes Tab

              PageStack {
                  id: notesTab

                  Page {
                      id: genericNotesPage

                      Item {
                          anchors.fill: parent
                          anchors.margins: styles.defaultSpacing

                          Column {
                              spacing: styles.defaultSpacing

                              Label {
                                  id: notesLbl
                                  text: qsTr("Notes:")
                                  color: styles.defaultLabelTextColor
                              }


                              TextArea {
                                  id: genericNotesEdit
                                  width: manualEventScreen.textFieldWidth
                                  height: 300
                                  wrapMode: TextEdit.Wrap
                                  clip:true
                              }

                          }

                      }

                  }

                  // --- Medicine Page ---

                  Page {
                      id: medicineNotesPage

                      Flickable {
                          anchors.fill: parent
                          anchors.margins: styles.defaultSpacing

                          Column {
                              spacing: styles.defaultSpacing

                              Label {
                                  color: styles.defaultLabelTextColor
                                  text: qsTr("Medicine name?")
                              }

                              TextField {
                                  id: medicineNameField
                                  width: manualEventScreen.textFieldWidth
                                  text: ""
                              }

                              Label {
                                  id: medicineNotesLbl
                                  color: styles.defaultLabelTextColor
                                  text: qsTr("Notes:")
                              }


                              TextArea {
                                  id: medicineNotesEdit
                                  width: manualEventScreen.textFieldWidth
                                  height: 200
                                  wrapMode: TextEdit.Wrap
                                  clip:true
                              }

                          }
                      }
                  }


                  //  --- Measures Page  ---

                  Page {
                      id: measuresNotesPage

                      Flickable {
                          anchors.fill: parent
                          anchors.margins: styles.defaultSpacing

                          Column {
                              spacing: styles.defaultSpacing

                              Label {
                                  color: styles.defaultLabelTextColor
                                  text: qsTr("Weight?")
                              }

                              TextField {
                                  id: weightEdit
                                  width: manualEventScreen.textFieldWidth
                                   text: ""
                                   validator: DoubleValidator{bottom: 0; top: 1000; decimals: 2}
                              }

                              Label {
                                  color: styles.defaultLabelTextColor
                                  text: qsTr("Height?")
                              }

                              TextField {
                                  id: heightEdit
                                  width: manualEventScreen.textFieldWidth
                                   text: ""
                                   validator: DoubleValidator{bottom: 0; top: 1000; decimals: 2}
                              }

                              Label {
                                  color: styles.defaultLabelTextColor
                                  text: qsTr("Cephalic perimeter?")
                              }

                              TextField {
                                  id: cephalicEdit
                                  width: manualEventScreen.textFieldWidth
                                  text: ""
                                  validator: DoubleValidator{bottom: 0; top: 1000; decimals: 2}
                              }
                          }
                      }
                  }

              }


              //  --- Recurrence Page  ---

              Page {
                  id: recurrenceTab

                  Item {
                      anchors.fill: parent
                      anchors.margins: styles.defaultSpacing

                      Column {
                          spacing: styles.defaultSpacing

                          Row {
                              spacing: styles.defaultSpacing

                              Label {
                                  height: parent.height
                                  color: styles.defaultLabelTextColor
                                  verticalAlignment: "AlignVCenter"
                                  text: qsTr("End date:")
                              }

                              ToolButton {
                                  platformInverted: true
                                  id: endDateBtn
                                  width: 240
                                  text: getDateText(endDateYear, endDateMonth, endDateDay)
                                  onClicked: endDateDlg.open();
                              }
                          }

                          Row {
                              spacing: styles.defaultSpacing

                              Label {
                                  height: parent.height
                                  color: styles.defaultLabelTextColor
                                  verticalAlignment: "AlignVCenter"
                                  text: qsTr("Repeat in (Hrs):")
                              }

                              TextField {
                                  id: intervalField
                                  width: 70
                                  text: "24"
                                  validator: IntValidator{bottom: 1; top: 24;}
                              }
                          }
                      }
                  }

              }
        }

        ToolBar {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 70
            id: eventsBar

            tools:ToolBarLayout {
                ButtonRow {
                    id: eventTypeBtnRow
                    checkedButton: leftFeedBtn
                    anchors.fill: parent
                    height: 70

                    EventButton {
                        id: leftFeedBtn
                        iconSource: "qrc:/icons/icons/breastfeeding-left.png"
                        height: 70
                        onClicked: handleLeftFeedBtn();
                    }

                    EventButton {
                        id: bottleFeedBtn
                        iconSource: "qrc:/icons/icons/baby_bottle.png"
                        height: 70
                        onClicked: handleBottleFeedBtn();
                    }

                    EventButton {
                        id: rightFeedbtn
                        iconSource: "qrc:/icons/icons/breastfeeding-right.png"
                        onClicked: handleRightFeedBtn();
                        height: 70
                    }

                    EventButton {
                        id: nappyBtn
                        iconSource: "qrc:/icons/icons/nappy.png"
                        height: 70
                        onClicked: handleNappyBtn();
                    }

                    EventButton {
                        id: medicineBtn
                        height: 70
                        iconSource: "qrc:/icons/icons/Pills.png"
                        onClicked: handleMedicineBtn();
                    }

                    EventButton {
                        id: measuresBtn
                        iconSource: "qrc:/icons/icons/weight.png"
                        height: 70
                        onClicked: handleMeasuresBtn();
                    }
                }
            }
        }

    }


    ToolBarLayout {
        id: toolbar
        visible: true

        ToolButton {
            text: qsTr("Save")
            onClicked: handleSave();
        }

        ToolButton {
            text: qsTr("Cancel")
            onClicked: manualEventScreen.canceled();
        }
    }

    DatePickerDialog {
        id: startDateDlg
        minimumYear: (new Date()).getFullYear()-10
        maximumYear: (new Date()).getFullYear()+1
        titleText: qsTr("Enter start date")
        acceptButtonText: qsTr("Change");
        rejectButtonText: qsTr("Cancel");
        onAccepted: {
            endDateDlg.day=startDateDlg.day;
            endDateDlg.month=startDateDlg.month;
            endDateDlg.year=startDateDlg.year;
        }
    }

    DatePickerDialog {
        id: endDateDlg
        minimumYear: (new Date()).getFullYear()-10
        maximumYear: (new Date()).getFullYear()+1
        titleText: qsTr("Enter end date")
        acceptButtonText: qsTr("Change");
        rejectButtonText: qsTr("Cancel");
    }

    TimePickerDialog {
        id: startTimeDlg
        titleText: qsTr("Enter start time")
        acceptButtonText: qsTr("Change");
        rejectButtonText: qsTr("Cancel");
    }

    onVisibleChanged: {
        notesTab.push(genericNotesPage);
    }

    function getDateText(year, month, day) {
        return (new Date(year, month-1, day)).toDateString();
    }

    function getTimeText(hour, minute) { 
        return hour+":"+minute;
    }

    function handleLeftFeedBtn() {
        eventTypeIndex=0;
        if (tabGroup.currentTab==recurrenceTab)
            tabGroup.currentTab=whenTab;
        if (notesTab.currentPage!=genericNotesPage)
            notesTab.replace(genericNotesPage);
        recurrenceTabBtn.enabled=false;
    }

    function handleBottleFeedBtn() {
        eventTypeIndex=1;
        if (tabGroup.currentTab==recurrenceTab)
            tabGroup.currentTab=whenTab;
        if (notesTab.currentPage!=genericNotesPage)
            notesTab.replace(genericNotesPage);
        recurrenceTabBtn.enabled=false;
    }

    function handleRightFeedBtn() {
        eventTypeIndex=2;
        if (tabGroup.currentTab==recurrenceTab)
            tabGroup.currentTab=whenTab;
        if (notesTab.currentPage!=genericNotesPage)
            notesTab.replace(genericNotesPage);
        recurrenceTabBtn.enabled=false;
    }

    function handleNappyBtn() {
        eventTypeIndex=3;
        if (tabGroup.currentTab==recurrenceTab)
            tabGroup.currentTab=whenTab;
        if (notesTab.currentPage!=genericNotesPage)
            notesTab.replace(genericNotesPage);
        recurrenceTabBtn.enabled=false;
    }

    function handleMedicineBtn() {
        eventTypeIndex=4;
        if (notesTab.currentPage!=medicineNotesPage)
            notesTab.replace(medicineNotesPage);
        recurrenceTabBtn.enabled=true;
    }

    function handleMeasuresBtn() {
        eventTypeIndex=5;
        if (tabGroup.currentTab==recurrenceTab)
            tabGroup.currentTab=whenTab;
        if (notesTab.currentPage!=measuresNotesPage)
            notesTab.replace(measuresNotesPage);
        recurrenceTabBtn.enabled=false;
    }

    function buttonFromIndex(index) {
        console.debug("qml:buttonFromIndex:"+index);
        switch(index) {
        case 0:
            return leftFeedBtn;
        case 1:
            return bottleFeedBtn;
        case 2:
            return rightFeedBtn;
        case 3:
            return nappyBtn;
        case 4:
            return medicineBtn;
        case 5:
            return measuresBtn;
        }
        return 0;
    }

    function setEventTypeIndex(index) {
        console.debug("qml:setEventTypeIndex:"+index);
        switch(index) {
        case 0:
            eventTypeBtnRow.checkedButton=leftFeedBtn;
            handleLeftFeedBtn();
            break;
        case 1:
            eventTypeBtnRow.checkedButton=bottleFeedBtn;
            handleBottleFeedBtn();
            break;
        case 2:
            eventTypeBtnRow.checkedButton=rightFeedBtn;
            handleRightFeedBtn();
            break;
        case 3:
            eventTypeBtnRow.checkedButton=nappyBtn;
            handleNappyBtn();
            break;
        case 4:
            eventTypeBtnRow.checkedButton=medicineBtn;
            handleMedicineBtn();
            break;
        case 5:
            eventTypeBtnRow.checkedButton=measuresBtn;
            handleMeasuresBtn();
            break;
        }
    }

    function handleSave() {
        if (eventTypeIndex==5) {
            if (!weightEdit.acceptableInput) {
                showMessageBox("Invalid weight");
                return;
            }

            if (!heightEdit.acceptableInput) {
                showMessageBox("Invalid height");
                return;
            }

            if (!cephalicEdit.acceptableInput) {
                showMessageBox("Invalid cephalic perimeter");
                return;
            }
        }

        manualEventScreen.save();
    }
}
