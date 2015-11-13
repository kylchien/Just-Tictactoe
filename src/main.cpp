#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include "tictactoe.h"


int main(int argc, char *argv[])
{
    //autogen code
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    static game::TicTacToe gameInstance;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("gameInstance", &gameInstance);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    //gameInstance.loadBoard(" x   xoox");

    return app.exec();
}

// x
//  x
//oox

