import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import QtMultimediaKit 1.1

Page {
    id: babyScreen
    objectName: "babyScreen"
    tools: toolbar
    orientationLock: PageOrientation.LockPortrait

    signal canceled()
    signal save()
    signal notificationChanged(int index, string type)

    property alias pageTitleText: title.title
    property string photoUrl: ""
    property alias name: nameField.text
    property alias birthdayDay: birthdayDlg.day
    property alias birthdayMonth: birthdayDlg.month
    property alias birthdayYear: birthdayDlg.year
    property int genderIndex: 0
    property alias timerAlarmsEnabled: timerAlarmsSwitch.checked
    property alias minutesInterval: minutesIntervalField.text
    property bool newBaby: true
    property bool photoChanged: false
    property alias capturedPhotoPath: camera.capturedImagePath

    Image {
        anchors.fill: parent
        fillMode: Image.Stretch
        source: "qrc:/resources/resources/main_screen_bgr.png"
        smooth: true
    }

    PageTitle {
        id: title
        anchors.top: parent.top
        title: "BabyFeed - Edit baby"
    }

    ToolBarLayout  {
         id: tabsToolBar
         anchors.top: title.bottom
         anchors.topMargin: 8
         anchors.left: parent.left
         anchors.right: parent.right
         height: 50

         ButtonRow {
             TabButton { id:babyTabBtn; tab: babyTab; text: qsTr("Baby") }
             TabButton { id:alarmTabBtn; tab: alarmsTab; text: qsTr("Alarms") }
             TabButton { id:notificationsTabBtn; tab: notificationsTab; text: qsTr("Notifications") }
         }

     }

    TabGroup {
          id: tabGroup
          anchors.top: tabsToolBar.bottom
          anchors.left: parent.left
          anchors.right: parent.right
          anchors.bottom: toolbar.top
          anchors.topMargin: 20

          currentTab: babyTab

          Page {
              id: babyTab

              Item {
                  anchors.fill: parent
                  anchors.margins: styles.defaultSpacing

                  Column {
                      spacing: styles.defaultSpacing

                      Label {
                          text: qsTr("Photo:")
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Image {
                              id: photoImage
                              width: 120
                              fillMode: Image.PreserveAspectFit
                              source: getPhotoSource();
                          }

                          Button {
                              id: photoBtn
                              iconSource: "qrc:/icons/icons/camera-photo.png"
                              onClicked: showCameraDialog();
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Name:")
                              width: 120
                          }

                          TextField {
                              id: nameField
                              width: 320
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Birthday:")
                              width: 120
                          }

                          Button {
                              id: birthdayBtn
                              text: getDateText(birthdayYear, birthdayMonth, birthdayDay)
                              onClicked: birthdayDlg.open();
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Gender:")
                              width: 120
                          }

                          Button {
                              id: genderBtn
                              text: getGenderText(babyScreen.genderIndex)
                              onClicked: babyGenderMenu.open();
                          }
                      }
                 }
              }
          }

          /* Alarms */

          Page {
              id: alarmsTab

              Item {
                  anchors.fill: parent
                  anchors.margins: styles.defaultSpacing

                  Column {
                      spacing: styles.defaultSpacing

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Timer alarms active ?")
                          }

                          Switch {
                              id: timerAlarmsSwitch
                              checked: true
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Min. between feeds:")
                          }

                          TextField {
                              id: minutesIntervalField
                              width: 90
                              text: "120"
                              validator: IntValidator{bottom: 1; top: 999;}
                          }
                      }
                  }
              }
          }


          /* Notifications */

          Page {
              id: notificationsTab

              Component {
                  id: contactRecord

                  Rectangle {
                      width: contactsView.width
                      height: 80
                      Row {
                          anchors.fill: parent
                          anchors.margins: 10
                          spacing: 10

                          Image {
                              source: icon
                              sourceSize.width: 48
                          }

                          Text {
                              text: (contactName==="no_contacts"?"<No Contacts>":contactName)
                              font.pointSize: styles.textHeadingSize
                          }
                      }

                      MouseArea {
                          anchors.fill: parent
                          onClicked: {if (contactName!="no_contacts") menuItemClicked(index, notificationType);}
                      }
                  }
              }

              ListView {
                  id: contactsView
                  anchors.top: parent.top
                  anchors.topMargin: -10
                  width: 480
                  height: 606
                  clip: true
                  delegate: contactRecord
                  model: contactsModel
              }

          }
    }

    ToolBarLayout {
        id: toolbar
        visible: true

        ToolIcon {
            iconId: "toolbar-back"
            onClicked: babyScreen.canceled();
        }

        ToolIcon {
            anchors.right: parent.right
            iconId: "toolbar-done"
            onClicked: handleSave();
        }
    }

    DatePickerDialog {
        id: birthdayDlg
        minimumYear: (new Date()).getFullYear()-10
        maximumYear: (new Date()).getFullYear()
        titleText: qsTr("Enter birthday")
        acceptButtonText: qsTr("Change");
        rejectButtonText: qsTr("Cancel");
    }

    Menu {
         id: babyGenderMenu
         MenuLayout {
             MenuItem {text: qsTr("Boy"); onClicked: setGender(0);}
                 MenuItem {text: qsTr("Girl"); onClicked: setGender(1);}
         }
    }

    Menu {
         id: notificationsMenu
         property int index: 0
         property string type: ""
         MenuLayout {
             MenuItem {text: (notificationsMenu.type===""?"(v)":"")+qsTr("No notifications"); onClicked: notificationChanged(notificationsMenu.index, ""); }
             MenuItem {text: (notificationsMenu.type==="F"?"(v)":"")+qsTr("Notify feeding"); onClicked: notificationChanged(notificationsMenu.index, "F"); }
             MenuItem {text: (notificationsMenu.type==="M"?"(v)":"")+qsTr("Notify medicine"); onClicked: notificationChanged(notificationsMenu.index, "M"); }
             MenuItem {text: (notificationsMenu.type==="P"?"(v)":"")+qsTr("Notify diaper"); onClicked: notificationChanged(notificationsMenu.index, "P"); }
             MenuItem {text: (notificationsMenu.type==="B"?"(v)":"")+qsTr("Notify all"); onClicked: notificationChanged(notificationsMenu.index, "B"); }
         }
    }

    Dialog {
        id: cameraDialog

        Camera {
            id: camera
            focus : visible // to receive focus and capture key events when visible
            width : 0
            height : 0
            flashMode: Camera.FlashRedEyeReduction
            whiteBalanceMode: Camera.WhiteBalanceFlash
            exposureCompensation: -1.0
            captureResolution: "320x240"
            anchors.centerIn: parent

            onImageCaptured : {
                photoImage.source = preview  // Show the preview in an Image element
            }
        }

        Button {
            id: captureBtn
            visible: false
            anchors.top: camera.bottom
            anchors.horizontalCenter: camera.horizontalCenter
            anchors.topMargin: styles.defaultSpacing
            text: qsTr("Capture");
            onClicked: handleCaptureBtnClick();
        }

        onRejected: handleCameraDlgRejected();
    }

    function getDateText(year, month, day) {
        return (new Date(year, month-1, day)).toDateString();
    }


    function getGenderText(index) {
        if (index === 0)
            return qsTr("Boy");
        else
            return qsTr("Girl");
    }

    function menuItemClicked(index, notificationType) {
        console.debug("menuItemClicked:"+index+","+notificationType);
        notificationsMenu.type=notificationType;
        notificationsMenu.index=index
        notificationsMenu.open();
    }

    function showCameraDialog() {
        camera.stop();
        camera.start();
        console.debug("camera started");
        camera.width=320;
        camera.height=240;
        cameraDialog.open();
        captureBtn.visible=true;
    }

    function handleCameraDlgRejected() {
        camera.stop();
        console.debug("camera stopped");
    }


    function handleCaptureBtnClick() {
        camera.captureImage();
        console.debug("photo captured to "+camera.capturedImagePath);
        camera.stop();
        console.debug("camera stopped");
        cameraDialog.accept();
        photoChanged=true;
    }

    function setGender(index) {
        babyScreen.genderIndex=index;
        if (newBaby) {
            if (index===0)
                photoImage.source="qrc:/icons/icons/baby_boy_icon.png";
            else
                photoImage.source="qrc:/icons/icons/baby_girl_icon.png";
        }
    }

    function getPhotoSource() {
        if (newBaby)
            return "qrc:/icons/icons/baby_boy_icon.png";
        else
            return photoUrl;
    }

    function handleSave() {
        if (!minutesIntervalField.acceptableInput) {
            showMessageBox("Please enter a valid feed interval");
            return;
        }

        babyScreen.save();
    }

    Component.onCompleted: {
        camera.stop();
    }
}
