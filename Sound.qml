import QtQuick 2.0
import QtMultimedia 5.5 //for sound

Item {
    property alias blop: blopSound
    property alias tick: tickSound
    property alias finish: finishSound

    Audio {
        id: bgm
        source: "asset/VacationUke.mp3"
        autoPlay: true
        loops: Audio.Infinite
        volume: 0.7
    }

    Audio {
        id: blopSound
        source: "asset/blop.mp3"
        loops: 1
    }

    Audio {
        id: tickSound
        source: "asset/tick.mp3"
        loops: 1
    }

    Audio {
        id: finishSound
        source: "asset/EndGame.mp3"
        loops: 1
    }
}

