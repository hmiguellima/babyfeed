import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Page {
    id: root
    orientationLock: PageOrientation.LockPortrait

    property string image: ""
    property int timeout: 1000
    property int fadeout: 500

    signal finished

    function activate() {
        animation.start();
    }

    anchors.fill: parent

    Image {
        id: splash

        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: root.image
    }

    SequentialAnimation {
        id: animation

        PauseAnimation { duration: root.timeout }

        PropertyAnimation {
            target: splash
            properties: "opacity"
            duration: root.fadeout
            to: 0
        }

        ScriptAction { script: finished(); }
    }
}
