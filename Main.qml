import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Chess 1.0

Window {
    visible: true
    width: 900
    height: 800
    title: "Chess Game"
    color: "#f0f0f0"

    ChessGUI {
        id: chessGame
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Status Bar
        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#2c3e50"

            Text {
                anchors.centerIn: parent
                text: chessGame.statusMessage
                color: "white"
                font.pixelSize: 20
                font.bold: true
            }
        }

        // Chess Board
        Rectangle {
            Layout.alignment: Qt.AlignCenter
            width: Math.min(parent.width, parent.height - 100)
            height: width
            color: "#34495e"

            Grid {
                id: board
                anchors.fill: parent
                rows: 8
                columns: 8

                Repeater {
                    model: 64
                    delegate: Rectangle {
                        id: square
                        width: parent.width / 8
                        height: parent.height / 8
                        color: {
                            const row = Math.floor(index / 8)
                            const col = index % 8
                            return (row + col) % 2 === 0 ? "#ecf0f1" : "#95a5a6"
                        }

                        property int row: Math.floor(index / 8)
                        property int col: index % 8
                        

                        Text {
                            anchors.centerIn: parent
                            text: {
                                const piece = chessGame.boardState[row][col]
                                return piece || ""
                            }
                            font.pixelSize: parent.width * 0.8
                            font.bold: true
                            font.family: "Arial"
                            color: {
                                const piece = chessGame.boardState[row][col]
                                if (!piece) return "transparent"
                                const isWhitePiece = chessGame.boardState[row][col] === chessGame.boardState[row][col].toUpperCase()
                                return isWhitePiece ? "#2c3e50" : "#e74c3c"  // Darker color for black pieces
                            }


                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                chessGame.handleSquareClick(row, col)
                                // chessGame.highlightedSquare = { row: row, col: col }  // Set the clicked square to be highlighted
                            }
                        }
                    }
                }
            }
        }

        // Coordinates (A, B, C, D, E, F, G, H)
        Row {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: board.width
            spacing: board.width / 8  // Adjust spacing to fit the board's width evenly

            Repeater {
                model: ["A", "B", "C", "D", "E", "F", "G", "H"]
                Text {
                    text: modelData
                    font.pixelSize: 16
                    color: "#2c3e50"
                    anchors.verticalCenter: parent.verticalCenter  // Vertically center the labels
                    //anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

    }

    // Update your Dialog to use the gameOver property
    Dialog {
        id: gameOverDialog
        title: "Game Over"
        modal: true
        visible: chessGame.gameOver
        anchors.centerIn: parent

        Text {
            text: chessGame.statusMessage
            font.pixelSize: 20
        }

        standardButtons: Dialog.Close | Dialog.Reset

        onAccepted: {
            chessGame.resetGame()
        }
        onRejected: {
            Qt.quit()
        }
    }

    // Update the status message text to use the new property
    // Text {
    //     anchors.centerIn: parent
    //     text: chessGame.statusMessage
    //     color: "white"
    //     font.pixelSize: 50
    //     font.bold: true
    // }

    // Connections to handle game events
    Connections {
        target: chessGame
        function onCheckMateOccurred(isWhiteWinner) {
            gameOverDialog.open()
        }
    }
}
