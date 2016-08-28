#include "viewModel.h"
#include "util/runtimeEx.h"
#include "util/timer.h"

#include <stdexcept>
#include <iostream>
#include <memory>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


using namespace std;
using namespace game;


#define TRY_CATCH_START try{

#define TRY_CATCH_END }\
    catch(const std::runtime_error& e){ \
        cerr << e.what() << endl; \
    }\
    catch (const std::invalid_argument& ia) { \
          std::cerr << "Invalid argument: " << ia.what() << '\n'; \
    } \
    catch (const std::out_of_range& oor) { \
        std::cerr << "Out of Range error: " << oor.what() << '\n'; \
    } \
    catch(...){ \
        cerr << "unhandled exception!!!" << endl; \
    }

int main(int argc, char *argv[])
{
    bool gui = true;


    if(gui){
        TRY_CATCH_START
            QApplication app(argc, argv);
            QQmlApplicationEngine engine;
            QQmlContext* ctx = engine.rootContext();

            static game::ViewModel vm;
            ctx->setContextProperty("tictactoe", &vm);

            engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

            //depth testing, ai:o
            //vm.loadBoard("~x~~~xoox");
            app.exec();
        TRY_CATCH_END

    }else{
        TRY_CATCH_START
            util::Timer timer;
            Engine engine;
            //engine.loadBoard("~o~~x~~~~");
            engine.run();
            cout << timer.elapse() << endl;
        TRY_CATCH_END

    }
    return 0;
}//main



