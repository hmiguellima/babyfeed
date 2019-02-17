import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Page {
    id: reportsScreen
    objectName: "reportsScreen"
    tools: toolbar
    orientationLock: PageOrientation.LockPortrait

    signal back()
    signal reportIndexChanged(int index)

    property alias pageTitleText: title.title
    property int currentIndex: fireIndexChanged(view.currentIndex)

    PageTitle {
        id: title
        anchors.top: parent.top
        title: "Reports"
        fontSize: styles.textHeadingSize
    }

    Rectangle {
         id: reportPages
         color: "lightgray"
         anchors.top: title.bottom
         anchors.left: parent.left
         anchors.right: parent.right
         anchors.bottom: parent.bottom

         Component {
             id: report

             Image {
                 width: view.width
                 height: view.height
                 source: modelData
             }
         }

         ListView {
             id: view
             anchors { fill: parent; bottomMargin: 30 }
             model: reportsModel
             preferredHighlightBegin: 0; preferredHighlightEnd: 0
             highlightRangeMode: ListView.StrictlyEnforceRange
             orientation: ListView.Horizontal
             snapMode: ListView.SnapOneItem; flickDeceleration: 2000
             cacheBuffer: 2
             delegate: report
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

    }

    ToolBarLayout {
        id: toolbar
        visible: true

        ToolIcon {
            id: backBtn
            iconId: "toolbar-back"
            onClicked: reportsScreen.back();
        }
    }

    function fireIndexChanged(index) {
        reportsScreen.reportIndexChanged(index);
        return index;
    }

}
