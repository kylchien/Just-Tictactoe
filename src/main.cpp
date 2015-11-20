#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "tictactoe.h"
#include "config.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    static game::TicTacToe gameInstance;


    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("gameInstance", &gameInstance);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    //depth testing, ai:o
    //gameInstance.loadBoard("~x~~~xoox");



    //doWin
    //gameInstance.loadBoard("oo~xx~x~~");

    //doBlock
    //gameInstance.loadBoard("~oxx~ox~~");

    //doFork, ai: x
    //gameInstance.loadBoard("~~oox~x~~");

    //doBlockFork, ai:x
    //gameInstance.loadBoard("~~xxo~o~~");

    //doConnectTwo, ai:o
    //gameInstance.loadBoard("~~x~o~x~~");

    //gameInstance.loadBoard("x~ooxxx~o");

    //gameInstance.rotateCW90();

    //Config config;
    //config.load();

    return app.exec();


    //return 0;
}

// x
//  x
//oox

//x
//oox
//x

//x~o
//oxx
//x~o
