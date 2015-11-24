import QtQuick 2.5
import QtQuick.Controls 1.2
//import QtQuick.Layouts 1.0
//import QtQuick.Controls.Styles 1.4


ApplicationWindow {
    id: gameWindow
    visible: true
    title: qsTr("Tic-Tac-Toe")

    width: boardImage.width
    height: boardImage.height     //+statusBar.implicitHeight+toolBar.implicitHeight
    minimumWidth: 420
    maximumWidth: 420
    minimumHeight: 515
    maximumHeight: 515

    Image {
        id: boardImage
        source: "asset/board.png"
        opacity: 0.5
        anchors.centerIn: parent

    }

    property var game: gameInstance
    property var optionWindow

    Component.onCompleted: {
        initOptionWindow()
    }

    Column {
        id: mainBoard
        anchors.centerIn:parent
        Grid {
            id: board
            width: boardImage.width; height: boardImage.height
            columns: 3

            Repeater {
                model: 9
                TicTacGrid {
                    objectName: "TicTacGrid" + modelData
                    width: board.width/3; height: board.width/3
                    onClicked: {
                        handleGridClick(index);
                    }
                }
            }
        }
    }

    Sound{
        id: sound
    }

    /*
    toolBar:ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                iconSource: "new.png"
            }
            ToolButton {
                iconSource: "open.png"
            }
            ToolButton {
                iconSource: "save-as.png"
            }
            Item { Layout.fillWidth: true }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
        }
    }
    statusBar: StatusBar {
        Label { text: "Read3 Only" }
        style: StatusBarStyle {
            padding {
                left: 8
                right: 8
                top: 3
                bottom: 3
            }
            background: Rectangle {
                implicitHeight: 50
                implicitWidth: gameWindow.width
                gradient: Gradient{
                    GradientStop{color: "#eee" ; position: 0}
                    GradientStop{color: "#ccc" ; position: 1}
                }
                Rectangle {
                    anchors.top: parent.top
                    width: gameWindow.width
                    height: 50
                    //http://www.w3.org/TR/SVG/types.html#ColorKeywords
                    color: "lavender"
                }
            }
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
            if(gameInstance.getCurrentTurn() == 'x')
                sound.tick.play();
            else
                sound.blop.play();

        }
    }

    Connections {
        target: game
        onGameFinished: {
            messageDisplay.text = message
            messageDisplay.visible = true
            sound.finish.play();
        }
    }

    Connections{
        target: game
        onWinningPositions:{
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

    function handleGridClick(index)
    {
        //prohibt click signal triggers after game over
        if(messageDisplay.visible == false &&
            optionWindow.visible == false){
            //prohibt user quickly clicks before AI moves
            if(game.isHumanTurn()){
                game.updateBoard(index);
            }
        }
    }
}

