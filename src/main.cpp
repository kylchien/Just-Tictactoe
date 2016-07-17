#include "viewModel.h"
#include "gameUtil.h"
#include "util/runtimeEx.h"
#include "util/timer.h"

//unecessary/////////////////////////////////////////
#include "lookupTable.h"
#include "agent/agentFactory.h"
#include "agent/qLearning.h"
#include "io/simpleReader.h"
#include "stateInfo.h"
// ///////////////////////////////////////////////

#include <stdexcept>
#include <iostream>
#include <memory>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


using namespace std;
using namespace game;

//QApplication that supports catching exception
class QApplicationEx : public QApplication
{
public:
    QApplicationEx(int &argc, char ** argv):QApplication(argc, argv){}
    ~QApplicationEx() = default;
    QApplicationEx(const QApplicationEx& src) = delete;
    QApplicationEx& operator=(const QApplicationEx& src) = delete;

private:
    bool notify(QObject* receiver, QEvent* event) override{
        try {
            return QApplication::notify(receiver, event);
        } catch(const util::RuntimeException& e){
            cerr << e.what() << endl;
            return false;
        }
    }
};

int main(int argc, char *argv[])
{
    bool gui = true;

    if(gui){
        QApplicationEx app(argc, argv);
        QQmlApplicationEngine engine;
        QQmlContext* ctx = engine.rootContext();

        static game::ViewModel vm;
        ctx->setContextProperty("tictactoe", &vm);

        engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

        //depth testing, ai:o
        //vm.loadBoard("~x~~~xoox");
        return app.exec();

    }else{
        try{
            util::Timer timer;
            Engine engine;
            engine.run();
            cout << timer.elapse() << endl;
        }
        catch(const std::runtime_error& e){
            cerr << e.what() << endl;
        }
        catch (const std::invalid_argument& ia) {
              std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
        }
        catch(...){
            cerr << "unhandled exception!!!" << endl;
        }
        return 0;
    }
}//main



