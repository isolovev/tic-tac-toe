import QtQuick 2.0
import TicTacToe

Flipable {
    id: root

    height: width
    width: 100

    property var state: TicTacToeModel.Unknown
    property bool flipped: state != TicTacToeModel.Unknown
    signal moveDone

    front: Rectangle {
        anchors.fill: parent
        color: "green"
    }

    back: Rectangle {
        id: backSide
        anchors.fill: parent
        color: "red"
        Image {
            id: img
            anchors.fill: parent
            // Complex condition to prevent source change while resetting the
            // model and flipping back to front rectangle.
            source: root.state == TicTacToeModel.Unknown
                    ? img.source : (root.state == TicTacToeModel.Cross)
                      ? "qrc:///images/cross.png" : "qrc:///images/ellips.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    transform: Rotation {
        origin {
            x: root.width / 2
            y: root.height / 2
        }
        axis {
            x: 0
            y: 1
            z: 0
        }
        angle: root.flipped ? 180 : 0
        Behavior on angle {
            NumberAnimation {
                duration: 500
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.moveDone()
        }
    }

}
