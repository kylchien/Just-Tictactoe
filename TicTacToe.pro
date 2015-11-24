TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/tictactoe.cpp \
    src/utility.cpp \
    src/player.cpp \
    src/ai/minimax.cpp \
    src/gameEngine.cpp \
    src/gameDef.cpp \
    src/config.cpp \
    src/ai/maybePerfect.cpp


RESOURCES += qml.qrc \
    resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/utility.h \
    src/tictactoe.h \
    src/player.h \
    src/ai/ai.h \
    src/ai/minimax.h \
    src/gameEngine.h \
    src/gameDef.h \
    src/config.h \
    src/ai/maybePerfect.h


