TEMPLATE = app

QT += qml quick widgets

#CONFIG += c++14 console
CONFIG += c++14

INCLUDEPATH += \
    $$PWD/src/util \
    $$PWD/src/io \
    $$PWD/src

SOURCES += \
    src/util/random.cpp \
    src/io/config.cpp \
    src/io/jsonReader.cpp \
    src/io/simpleWriter.cpp \
    src/io/simpleReader.cpp \
    src/agent/maybePerfect.cpp \
    src/agent/agentFactoryImpl.cpp \
    src/agent/agentFactory.cpp \
    src/agent/minimax.cpp \
    src/agent/negmax.cpp \
    src/player.cpp \
    src/engine.cpp \
    src/engineImpl.cpp \
    src/viewModel.cpp \  
    src/main.cpp \
    src/gameUtil.cpp \
    src/lookupTable.cpp \
    src/agent/qLearning.cpp \
    src/stateInfo.cpp





RESOURCES += qml.qrc \
    resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/util/runtimeEx.h \
    src/util/random.h \
    src/util/timer.h \
    src/io/simpleWriter.h \
    src/io/simpleReader.h \
    src/io/jsonReader.h \
    src/io/config.h \
    src/gameDef.h \
    src/agent/agent.h \
    src/agent/agents.h \
    src/agent/maybePerfect.h \
    src/agent/minimax.h \
    src/agent/negmax.h \
    src/agent/agentFactory.h \
    src/agent/agentFactoryImpl.h \
    src/player.h \
    src/engine.h \
    src/engineImpl.h \
    src/viewModel.h \
    src/gameUtil.h \
    src/lookupTable.h \
    src/agent/qLearning.h \
    src/stateInfo.h







    

DISTFILES += \
    src/todo.txt


