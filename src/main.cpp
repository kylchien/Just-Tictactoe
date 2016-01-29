#include <stdexcept>
#include <iostream>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDateTime>
#include <QElapsedTimer>


#include "gameEngine.h"
#include "tictactoe.h"
#include "./io/config.h"
#include "./io/save.h"
#include "./util/utility.h"

//#include <QTime>
//#include <QDate>
#include "playerFactory.h"

#include <QDebug>

using namespace std;
using namespace game;
using namespace io;

int main(int argc, char *argv[])
{
    bool gui = true;

    if(gui){

    static game::TicTacToe gameInstance;

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("gameInstance", &gameInstance);

    //engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

    //depth testing, ai:o
    //gameInstance.loadBoard("~x~~~xoox");
	
    return app.exec();

    }else{

    try{
        util::Timer timer;
        Config config;
        GameEngine gameEngine(&config);
        gameEngine.run();
        cout << timer.elapse() << endl;
    }
	catch(const std::runtime_error& e){
		cerr << e.what() << endl;
	}
    catch(...){
        cerr << "unhandled exception!!!" << endl;
    }

    return 0;

    }


}

