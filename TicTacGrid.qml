import QtQuick 2.5

Item {
    signal clicked

    property alias blink: seqAnimation

    states: [
        State {
            name: "x";
            PropertyChanges { target: image; source: "asset/x.png" }
        },
        State {
            name: "o";
            PropertyChanges { target: image; source: "asset/o.png" }
        }
    ]

    Image {
        id: image
        anchors.centerIn: parent
        transform: Rotation {
            origin.x: image.width/2; origin.y: image.height/2;
            angle: Math.floor((Math.random() * 45) + 1) * randomSign();
        }

    }

    function randomSign(){
        if(Math.random()>0.5) return 1;
        else                  return -1;
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }



    SequentialAnimation on opacity{
        id: seqAnimation
        running: false   // Animations on properties start running by default
        loops: 3
        NumberAnimation { from: 1; to: 0; duration: 350; easing.type: Easing.InOutQuad }
        NumberAnimation { from: 0; to: 1; duration: 350; easing.type: Easing.InOutQuad }
    }


}

