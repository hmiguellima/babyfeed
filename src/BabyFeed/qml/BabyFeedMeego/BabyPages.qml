import QtQuick 1.0
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Rectangle {
     id: babyPages
     color: "lightgray"
     width: parent.width
     height: 150

     property alias model: view.model
     property alias currentBabyIndex: view.currentIndex
     // Trigger
     property int readOnlyIndex: fireIndexChange(view.currentIndex)

     Component {
         id: babyRecord

         Rectangle {
                  width: view.width
                  height: view.height

                  gradient: Gradient {
                          GradientStop { position: 0.3; color: "#E1E1E1" }
                          GradientStop { position: 1.0; color: "#7575FF" }
                      }
                  //border.color: "#67437D"
                  //border.width: 2

                  Row {
                      anchors.fill: parent
                      anchors.margins: styles.defaultSpacing
                      spacing: styles.defaultSpacing
                      Image {
                          source: photo
                          width: 120
                          fillMode: Image.PreserveAspectFit
                      }
                      Column {
                          Text {
                              text: name
                              font.pointSize: styles.textHeadingSize
                          }
                          Text {
                              text: age
                              font.pointSize: styles.textNormalSize
                          }
                          Text {
                              text: measures
                              font.pointSize: styles.textNormalSize
                          }
                      }
                  }

                  Image {
                      source: "qrc:/resources/resources/baby_btn_handle.png"
                      anchors.right: parent.right
                      anchors.rightMargin: 5
                      anchors.verticalCenter: parent.verticalCenter
                  }

                  MouseArea {
                      anchors.fill: parent
                      onClicked: babyRecordClicked(index, newBaby);
                  }
              }
     }

     ListView {
         id: view
         anchors { fill: parent; bottomMargin: 30 }
         model: itemModel
         preferredHighlightBegin: 0; preferredHighlightEnd: 0
         highlightRangeMode: ListView.StrictlyEnforceRange
         orientation: ListView.Horizontal
         snapMode: ListView.SnapOneItem; flickDeceleration: 2000
         cacheBuffer: 2
         delegate: babyRecord
     }

     Rectangle {
         id: controller
         width: view.width; height: 27
         anchors { top: view.bottom; bottom: parent.bottom }

         gradient: Gradient {
                 GradientStop { position: 0.0; color: "#A2A5A6" }
                 GradientStop { position: 1.0; color: "#C3C5C6" }
         }

         Row {
             anchors.centerIn: parent
             spacing: 20

             Repeater {
                 model: view.model

                 Rectangle {
                     width: 5; height: 5
                     radius: 3
                     color: view.currentIndex == index ? "blue" : "white"

                     MouseArea {
                         width: 20; height: 20
                         anchors.centerIn: parent
                         onClicked: view.currentIndex = index
                     }
                 }
             }
         }
     }

     Image {
         anchors.top: controller.bottom
         width: parent.width
         height: 3
         source: "qrc:/resources/resources/bevel_h.png"
         fillMode: Image.TileHorizontally
     }

     Menu {
          id: babyMenu
          property int babyIndex: 0
          MenuLayout {
              MenuItem {text: qsTr("Edit"); onClicked: mainScreen.editBabyClicked(babyMenu.babyIndex);}
              MenuItem {text: qsTr("Delete"); onClicked:handleDeleteBabyClicked(babyMenu.babyIndex);}
          }
     }

     QueryDialog {
         id: confirmDeleteRecordDlg
         titleText: qsTr("Please confirm")
         acceptButtonText: qsTr("Delete")
         rejectButtonText: qsTr("Cancel")
         message: qsTr("Remove baby?")

         property int babyIndex: 0

         onAccepted: mainScreen.deleteBabyClicked(babyIndex);
     }

     function fireIndexChange(index) {
         mainScreen.babyIndexChanged(index);
         console.debug("qml:babyIndexChanged");
         return index;
     }


     function babyRecordClicked(index, newBaby) {
         if (newBaby)
             mainScreen.newBabyClicked();
         else {
             babyMenu.babyIndex=index;
             babyMenu.open();
         }
     }

     function handleDeleteBabyClicked(index) {
         confirmDeleteRecordDlg.babyIndex=index;
         confirmDeleteRecordDlg.open();
     }

     function positionToIndex(index) {
         view.positionViewAtIndex(index, ListView.Center);
     }
 }
