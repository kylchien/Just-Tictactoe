TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11 console

SOURCES += \
    src/util/utility.cpp \
    src/main.cpp \
    src/tictactoe.cpp \
    src/player.cpp \
    src/gameEngine.cpp \
    src/gameDef.cpp \
    src/playerFactory.cpp \
    src/io/config.cpp \
    src/io/save.cpp \
    src/ai/maybePerfect.cpp \
    src/ai/minimax.cpp \
    src/ai/negmax.cpp


RESOURCES += qml.qrc \
    resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/util/utility.h \
    src/tictactoe.h \
    src/player.h \
    src/ai/ai.h \
    src/ai/minimax.h \
    src/gameEngine.h \
    src/gameDef.h \
    src/ai/maybePerfect.h \
    src/playerFactory.h \
    src/io/config.h \
    src/io/save.h \
    src/ai/negmax.h

DISTFILES += \
    src/todo.txt


