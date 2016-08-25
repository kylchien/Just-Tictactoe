import QtQuick 2.5
import QtQuick.Window 2.1 // needed for the Window component
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4



Window {
    id: optionWindow
    title: "please choose play mode"
    height:radioButtonGroup.height + aiChooserGroupBox.height + okButton.height + 20
    width: radioButtonGroup.width + 10
    visible: true

    property ListModel playerX_AI_ListModel: ListModel {}
    property ListModel playerO_AI_ListModel: ListModel {}
    property var playerX_AI_ListModel_idx: 0
    property var playerO_AI_ListModel_idx: 0
    property var aiList: []

    //set the first option as default
    Component.onCompleted: {
        optionList.children[0].checked = true
        aiList = gameWindow.game.getAI()
        for(var i =0; i<aiList.length;++i){
           playerX_AI_ListModel.append({ aiType:aiList[i]} );
           playerO_AI_ListModel.append({ aiType:aiList[i]} );

           // we can access the object inside GroupBox via GroupBox.contentItem.children
           // aiRepeater.itemAt(0).contentItem.children[0].children[1].model.append({ aiType:list[i]} );
           // var columnInsideGroupBox = aiRepeater.itemAt(0).contentItem.children[0]
        }
    }


    GroupBox {
        id: radioButtonGroup
        Column {
            id: optionList
            spacing: 10
            ExclusiveGroup { id: optionGroup }
            Repeater{
                model: ["Human(x)\tvs\tHuman(o)",
                        "Human(x)\tvs\tMachine(o)",
                        "Machine(x)\tvs\tHuman(o)",
                        "Machine(x)\tvs\tMachine(o)"]
                RadioButton {
                    id: radioButton
                    exclusiveGroup: optionGroup
                    text: modelData
                    Accessible.onCheckedChanged: setAIChooserVisible()
                    style: RadioButtonStyle {
                        id: radioButtonStyle
                        label: Text {
                            renderType: Text.NativeRendering
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.family: "Helvetica"
                            font.pointSize: 12
                            color: "#555"
                            text: control.text
                        }
                    }//RadioButton style
                }//RadioButton
            }//repeater
        }//Column
    }//GroupBox

    Row{
        id: aiChooserGroupBox
        visible: false
        anchors.top: radioButtonGroup.bottom
        Repeater {
            id: aiRepeater
            model: ["X","O"]
            GroupBox {
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                Column{

                    Label{
                        text: "Player " + modelData + " AI:"
                    }

                    ComboBox{
                        currentIndex: 0
                        model: getListModel(modelData)
                        width: radioButtonGroup.width/2-15
                        onCurrentIndexChanged: {
                            setListModelIdx(modelData, currentIndex)
                        }
                    }//ComboBox
                }//Column
            }//GroupBox
        }//Repeater
    }//row


    Button {
        id: okButton
        text: "OK"
        height:50
        anchors.top: aiChooserGroupBox.bottom
        anchors.horizontalCenter: radioButtonGroup.horizontalCenter
        anchors.topMargin: 10

        onClicked: {
            var gameMode = 0
            for(var i =0; i<4; ++i){
                if(optionList.children[i].checked == true){
                    gameMode = i
                    break
                }
            }

            gameWindow.game.setGameMode(i)
            var playerX_aiType = playerX_AI_ListModel.get(playerX_AI_ListModel_idx).aiType
            var playerO_aiType = playerO_AI_ListModel.get(playerO_AI_ListModel_idx).aiType

            //console.debug(gameMode)
            //console.debug(playerX_aiType.aiType)
            //console.debug(playerO_aiType.aiType)
            gameWindow.game.createPlayers(gameMode, playerX_aiType, playerO_aiType)
            //gameWindow.game.createPlayers(gameMode, "Minimax", "Minimax")
            optionWindow.close()
        }

        onHoveredChanged: {
            hovered ? okButton.opacity = 0.7 : okButton.opacity = 1;
        }

        style: ButtonStyle{
            label: Text {
               renderType: Text.NativeRendering
               verticalAlignment: Text.AlignVCenter
               horizontalAlignment: Text.AlignHCenter
               font.family: "Helvetica"
               font.pointSize: 12
               color: "#555"
               text: control.text
           }
        }
    }

    function getListModel(playerMark)
    {
        if(playerMark == "X")
            return playerX_AI_ListModel;
        else
            return playerO_AI_ListModel;
    }

    function setListModelIdx(playerMark, idx)
    {
        if(playerMark == "X")
            playerX_AI_ListModel_idx = idx;
        else
            playerO_AI_ListModel_idx = idx;
    }

    function setAIChooserVisible(){
        if(optionList.children[0].checked ){
            aiChooserGroupBox.visible=false;
        }
        else if(optionList.children[1].checked ){
            aiChooserGroupBox.visible=true;
            aiRepeater.itemAt(0).visible = false;
            aiRepeater.itemAt(1).visible = true;
        }
        else if(optionList.children[2].checked ){
            aiChooserGroupBox.visible=true;
            aiRepeater.itemAt(0).visible = true;
            aiRepeater.itemAt(1).visible = false;
        }
        else if(optionList.children[3].checked ){
            aiChooserGroupBox.visible=true;
            aiRepeater.itemAt(0).visible = true;
            aiRepeater.itemAt(1).visible = true;
        }

    }

}
