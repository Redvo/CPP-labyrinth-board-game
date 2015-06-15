#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T11:21:11
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

CONFIG += c++11 release
CONFIG(release, debug|release) {
    TARGET = labyrinth2015
    DESTDIR = ../../
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
} else {
    TARGET = labyrinth2015_debug
    DESTDIR = ../../
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
}

#LIBS += -L../lib/ -llabyrinth

INCLUDEPATH += ../header/

SOURCES += main.cpp\
    gamewindow.cpp \
    gamemenu.cpp \
    ../source/arguments.cpp \
    ../source/cardpack.cpp \
    ../source/exception.cpp \
    ../source/game.cpp \
    ../source/gameboard.cpp \
    ../source/holdingtreasure.cpp \
    ../source/player.cpp \
    ../source/playerlist.cpp \
    ../source/stone.cpp \
    ../source/treasurecard.cpp

HEADERS  += gamewindow.h \
    gamemenu.h

FORMS    += gamewindow.ui \
    gamemenu.ui

RESOURCES += images.qrc
