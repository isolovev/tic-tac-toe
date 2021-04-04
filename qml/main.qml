import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import TicTacToe

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tic-Tac-Toe")

    TicTacToeModel {
        id: dataModel
        gridSize: 3
    }

    StackLayout {
        id: pages
        anchors.fill: parent

        GameMenu {
            id: menu
            dataModel: dataModel
            onResumeGame: {
                pages.currentIndex = 1
            }
            onStartGame: {
                dataModel.resetModel()
                pages.currentIndex = 1
            }
            onShowSettings: {
                console.log("show settings")
//                pages.currentIndex = 2
            }
        }

        GameWindow {
            id: game
            dataModel: dataModel
            onBackToMenu: {
                pages.currentIndex = 0
            }
        }
    }
}
