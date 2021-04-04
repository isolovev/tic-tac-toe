import QtQuick
import QtQuick.Controls

Item {
    id: root

    property var dataModel

    signal resumeGame
    signal startGame
    signal showSettings

    Column {
        spacing: 20
        anchors {
            centerIn: parent
        }

        Button {
            id: continueBtn
            text: qsTr("Continue")
            enabled: dataModel.gameInProgress
            onClicked: root.resumeGame()
        }
        Button {
            id: startBtn
            text: qsTr("Start")
            onClicked: root.startGame()
        }
        Button {
            id: menuBtn
            text: qsTr("Settings")
            onClicked: root.showSettings()
        }
    }
}
