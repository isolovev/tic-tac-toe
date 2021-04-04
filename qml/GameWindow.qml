import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import TicTacToe

Item {
    id: root

    signal backToMenu
    property int gridSize: 3
    property var dataModel

    Row {
        id: players
        anchors {
            top: parent.top
            margins: 20
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 50
        Repeater {
            model: 2
            delegate: Text {
                font.bold: index == dataModel.player
                text: qsTr("Player " + (index + 1))
            }
        }
    }

    Grid {
        id: grid
        anchors {
            top: players.bottom
            margins: 20
            bottom: gameResults.top
            horizontalCenter: parent.horizontalCenter
        }
        columns: dataModel.gridSize
        spacing: 10
        // grid width will be calculated based on the cell width and the amount
        // of cells, so the cell size shall use root.width
        property int cellSize: (Math.min(root.width, height) - spacing * (columns - 1)) / columns
        Repeater {
            id: cells
            model: dataModel
            delegate: Cell {
                width: grid.cellSize
                state: model.state
                onMoveDone: root.dataModel.click(index)
            }
        }
    }

    Text {
        id: gameResults
        anchors {
            bottom: back.top
            margins: 20
            horizontalCenter: root.horizontalCenter
        }
        text: (root.dataModel.gameStatus == TicTacToeModel.GameOverWin)
              ? qsTr("Player " + (root.dataModel.player + 1) + " won")
              : (root.dataModel.gameStatus == TicTacToeModel.GameOverDraw)
                ? qsTr("Game over: DRAW") : ""
    }

    Button {
        id: back
        anchors {
            bottom: parent.bottom
            margins: 20
            topMargin: 0
            left: parent.left
        }
        text: qsTr("Back")
        onClicked: root.backToMenu()
    }

    Button {
        id: restart
        anchors {
            verticalCenter: back.verticalCenter
            margins: 20
            topMargin: 0
            right: parent.right
        }
        text: qsTr("Restart")
        onClicked: dataModel.resetModel()
    }

}
