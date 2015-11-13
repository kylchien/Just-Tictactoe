import QtQuick 2.5
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: gameWindow
    visible: true
    title: qsTr("Tic-Tac-Toe")

    width: boardImage.width
    height: boardImage.height

    Image {
        id: boardImage
        source: "asset/board.png"
        anchors.centerIn: parent
    }

    property var game: gameInstance
    property var wait: false
    property var optionWindow

    Component.onCompleted: {
        initOptionWindow()
    }

    Column {
        id: mainBoard

        Grid {
            id: board
            width: boardImage.width; height: boardImage.height
            columns: 3

            Repeater {
                model: 9
                TicTacGrid {
                    objectName: "TicTacGrid" + modelData
                    width: board.width/3; height: board.height/3
                    onClicked: {
                        //if-clause prohibt click event triggers after game over
                        if(messageDisplay.visible == false &&
                            optionWindow.visible == false){
                            //wait = true;
                            //issue: player can click while ai is still thinking
                            game.updateBoard(index);
                        }
                    }
                }
            }
        }
    }

    /*
    Timer {
        id: forPerception
        interval: 100 //millisec
        running: wait
        onTriggered: {
            //game.notifyPlayers();
            wait = false;
        }
    }*/


    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Connections {
        target: game
        onBoardChanged: {
            board.children[pos].state = mark;
        }
    }

    Connections {
        target: game
        onGameFinished: {
            messageDisplay.text = message
            messageDisplay.visible = true
        }
    }

    Connections{
        target: game
        onConnected:{
            for(var i =0; i<list.length;++i){
                board.children[list[i]].blink.start()
            }
        }
    }

    Connections{
        target: game
        onBoardLoaded:{
            for(var i =0; i<list.length;++i){
                board.children[i].state = list[i];
            }
        }
    }

    Text {
        id: messageDisplay
        anchors.centerIn: parent
        color: "blue"
        style: Text.Outline; styleColor: "white"
        font.pixelSize: 50; font.bold: true
        visible: false

        Timer {
            interval: 2500 //millisec
            running: messageDisplay.visible
            onTriggered: {
                messageDisplay.visible = false; //turn itself off
                gameWindow.restart();
            }
        }
    }

    function initOptionWindow() {
        var component = Qt.createComponent("OptionWindow.qml");
        var ow = component.createObject(gameWindow);
        optionWindow = ow
        optionWindow.show();
    }

    function restart()
    {
        game.restart();
        for(var i=0; i < board.children.length; ++i){
            board.children[i].state = ""
        }
        optionWindow.show()
    }

}

