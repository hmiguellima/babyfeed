import QtQuick 1.0

Rectangle {
    property alias title: title.text
    property alias fontSize: title.font.pointSize

    height: 74
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
            anchors.leftMargin: 10
            anchors.topMargin: 5
            source: "qrc:/icons/icons/babyfeed_64_icon.png"
        }

        Item {
            anchors.fill: parent
            anchors.leftMargin: 80
            anchors.topMargin: 10
            anchors.rightMargin: 10
            anchors.bottomMargin: 10

            Text {
                id: title
                font.pointSize: styles.textTitleSize
                color: "#000000"
            }
        }
    }
}
