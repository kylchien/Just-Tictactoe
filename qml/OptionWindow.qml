import QtQuick 2.5
import QtQuick.Window 2.1 // needed for the Window component
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4



Window {
    id: optionWindow
    title: "please choose play mode"
    height:groupBox.height + okButton.height + 20
    width: groupBox.width + 10
    visible: true

    //set the first option as default
    Component.onCompleted: {
        optionList.children[0].checked = true
    }


    GroupBox {
        id: groupBox
        Column {
            id: optionList
            spacing: 10
            ExclusiveGroup { id: optionGroup }
            Repeater{
                model: ["Human(x) vs Human(o)",
                        "Human(x) vs Machine(o)",
                        "Machine(x) vs Human(o)",
                        "Machine(x) vs Machine(o)"]
                RadioButton {
                    id: radioButton
                    exclusiveGroup: optionGroup
                    text: modelData
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
                    }
                }
            }
        }

    }


    Button {
        id: okButton
        text: "OK"
        height:50
        anchors.top: groupBox.bottom
        anchors.horizontalCenter: groupBox.horizontalCenter
        anchors.topMargin: 10
        onClicked: {
            for(var i =0; i<4; ++i){
                if(optionList.children[i].checked == true){
                    gameWindow.game.setGameMode(i)
                }
            }
            optionWindow.close()
            gameWindow.game.createPlayers()

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

}
