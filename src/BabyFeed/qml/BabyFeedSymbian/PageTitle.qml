import QtQuick 1.1

Rectangle {
    property alias title: title.text
    property alias fontSize: title.font.pointSize

    height: 62
    width: parent.width

    Image {
        id: titleRect
        anchors.fill: parent
        anchors.margins: 0
        source: "qrc:/resources/resources/top_panel_tile.png"
        fillMode: Image.TileHorizontally

        Image {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: styles.defaultSpacing
            anchors.topMargin: styles.defaultSpacing
            width: 48
            fillMode: Image.PreserveAspectFit
            source: "qrc:/icons/icons/babyfeed_48_icon.png"
        }

        Item {
            anchors.fill: parent
            anchors.leftMargin: 60
            anchors.topMargin: styles.defaultSpacing
            anchors.rightMargin: styles.defaultSpacing
            anchors.bottomMargin: styles.defaultSpacing

            Text {
                id: title
                font.pointSize: styles.textTitleSize
                color: "#000000"
            }
        }
    }
}
