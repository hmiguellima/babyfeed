import QtQuick 1.1
import com.nokia.extras 1.1
import com.nokia.symbian 1.1
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

    PageTitle {
        id: title
        anchors.top: parent.top
        title: "BabyFeed - Edit baby"
    }

    TabBarLayout {
         id: tabsToolBar
         anchors.top: title.bottom
         anchors.topMargin: 0
         anchors.left: parent.left
         anchors.right: parent.right
         height: 50

         TabButton { id:babyTabBtn; tab: babyTab; text: qsTr("Baby") }
         TabButton { id:alarmTabBtn; tab: alarmsTab; text: qsTr("Alarms") }
         TabButton { id:notificationsTabBtn; tab: notificationsTab; text: qsTr("Notifications") }
     }

    TabGroup {
          id: tabGroup
          anchors.top: tabsToolBar.bottom
          anchors.left: parent.left
          anchors.right: parent.right
          anchors.bottom: toolbar.top

          currentTab: babyTab

          /* Baby Tab */

          Page {
              id: babyTab

              Image {
                  height: 640
                  width: 360
                  fillMode: Image.Stretch
                  source: "qrc:/resources/resources/main_screen_bgr.png"
                  smooth: true
              }

              Item {
                  anchors.fill: parent
                  anchors.margins: styles.defaultSpacing

                  Column {
                      spacing: styles.defaultSpacing

                      Label {
                          text: qsTr("Photo:")
                          color: styles.defaultLabelTextColor
                      }


                      Row {
                          spacing: styles.defaultSpacing

                          Image {
                              id: photoImage
                              width: 120
                              fillMode: Image.PreserveAspectFit
                              source: getPhotoSource();
                              cache: false
                          }

                          ToolButton {
                              id: photoBtn
                              text: qsTr("Capture")
                              iconSource: "qrc:/icons/icons/camera-photo.png"
                              platformInverted: true
                              onClicked: showCameraDialog();
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Name:")
                              verticalAlignment: "AlignVCenter"
                              height: parent.height
                              color: styles.defaultLabelTextColor
                              width: 80
                          }

                          TextField {
                              id: nameField
                              width: 230
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Birthday:")
                              verticalAlignment: "AlignVCenter"
                              height: parent.height
                              color: styles.defaultLabelTextColor
                              width: 80
                          }

                          ToolButton {
                              id: birthdayBtn
                              platformInverted: true
                              width: 230
                              text: getDateText(birthdayYear, birthdayMonth, birthdayDay)
                              onClicked: birthdayDlg.open();
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              text: qsTr("Gender:")
                              verticalAlignment: "AlignVCenter"
                              height: parent.height
                              color: styles.defaultLabelTextColor
                              width: 80
                          }

                          ToolButton {
                              id: genderBtn
                              platformInverted: true
                              width: 230
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

              Image {
                  height: 640
                  width: 360
                  fillMode: Image.Stretch
                  source: "qrc:/resources/resources/main_screen_bgr.png"
                  smooth: true
              }

              Item {
                  anchors.fill: parent
                  anchors.margins: styles.defaultSpacing

                  Column {
                      spacing: styles.defaultSpacing

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              color: styles.defaultLabelTextColor
                              text: qsTr("Timer alarms active ?")
                              verticalAlignment: "AlignVCenter"
                              height: parent.height
                          }

                          Switch {
                              id: timerAlarmsSwitch
                              checked: true
                          }
                      }

                      Row {
                          spacing: styles.defaultSpacing

                          Label {
                              color: styles.defaultLabelTextColor
                              text: qsTr("Min. between feeds:")
                              verticalAlignment: "AlignVCenter"
                              height: parent.height
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

              Image {
                  height: 640
                  width: 360
                  fillMode: Image.Stretch
                  source: "qrc:/resources/resources/main_screen_bgr.png"
                  smooth: true
              }

              Component {
                  id: contactRecord

                  Rectangle {
                      width: contactsView.width
                      height: 65
                      Row {
                          anchors.fill: parent
                          spacing: styles.defaultSpacing

                          Image {
                              source: icon
                              sourceSize.width: 48
                              anchors.verticalCenter: parent.verticalCenter
                          }

                          Text {
                              height: parent.height
                              verticalAlignment: "AlignVCenter"
                              text: contactName
                              font.pointSize: styles.textHeadingSize
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
                          visible: (notificationType===""?false:true)
                      }

                      MouseArea {
                          anchors.fill: parent
                          onClicked: {if (notificationType!=="") menuItemClicked(index, notificationType);}
                      }
                  }
              }

              ListView {
                  id: contactsView
                  height: 445
                  width: 360
                  clip: true
                  delegate: contactRecord
                  model: contactsModel
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
            text: qsTr("Cancel");
            onClicked: babyScreen.canceled();
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
        title: Label {
            width: parent.width
            height: parent.height
            horizontalAlignment: "AlignHCenter"
            verticalAlignment: "AlignVCenter"
            text: qsTr("Take a photo")
        }
        content: Item {
            width: 340
            height: 260

            Camera {
                id: camera
                focus : visible // to receive focus and capture key events when visible
                width : 0
                height : 0
                //flashMode: Camera.FlashRedEyeReduction
                //whiteBalanceMode: Camera.WhiteBalanceFlash
                //exposureCompensation: -1.0
                captureResolution: "320x240"
                anchors.centerIn: parent

                onImageCaptured : {
                    photoImage.source = preview;  // Show the preview in an Image element
                    console.debug("photo captured to "+camera.capturedImagePath);
                    stop();
                    console.debug("camera stopped");
                    cameraDialog.accept();
                    photoChanged=true;
                }
            }

        }

        buttons: Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: styles.defaultSpacing

                Button {
                    id: captureBtn
                    visible: false
                    //anchors.top: camera.bottom
                    //anchors.horizontalCenter: camera.horizontalCenter
                    //anchors.topMargin: styles.defaultSpacing
                    text: qsTr("Capture");
                    onClicked: handleCaptureBtnClick();
                }

                Button {
                    text: qsTr("Cancel")
                    onClicked: cameraDialog.reject();
                }
            }
        }

        onStatusChanged: if (cameraDialog.status==DialogStatus.Open) {
                             console.debug("camera dialog open");
                             camera.stop();
                             camera.start();
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
        console.debug("camera started");
        camera.width=320;
        camera.height=240;
        camera.stop();
        camera.start();
        cameraDialog.open();
        captureBtn.visible=true;
    }

    function handleCameraDlgRejected() {
        camera.stop();
        console.debug("camera stopped");
    }


    function handleCaptureBtnClick() {
        camera.captureImage();
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
