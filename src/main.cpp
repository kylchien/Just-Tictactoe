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
    //engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

    //Config config;
    //config.load();

    return app.exec();
}

