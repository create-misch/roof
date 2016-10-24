#-------------------------------------------------
#
# Project created by QtCreator 2016-06-08T21:37:45
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = roof
TEMPLATE = app

DESTDIR = ./

MOC_DIR = ./moc

OBJECTS_DIR = ./obj


SOURCES += main.cpp\
    options.cpp \
    menu/menuwindow.cpp \
    game/objects/object.cpp \    
    game/objects/pistolbehavior.cpp \
    game/objects/uzibehavior.cpp \
    game/objects/bullet.cpp \
    game/objects/myobject.cpp \
    game/objects/npcobject.cpp \
    game/engine.cpp \
    game/graphic.cpp \
    game/gamepanel.cpp \
    game/objects/wall.cpp \
    game/objects/rocketbehavior.cpp \
    game/objects/bot.cpp \
    game/objects/kamikaze.cpp \
    menu/singlegame.cpp \
    menu/windowsmanager.cpp \
    game/objects/wallbehavior.cpp \
    game/objects/fatbot.cpp \
    reader/levelsreader.cpp \
    reader/parser.cpp



HEADERS  += ./menu/menuwindow.h \
    options.h \
    game/objects/object.h \
    game/objects/pistolbehavior.h \
    game/objects/uzibehavior.h \
    game/objects/bulletbehavior.h \
    game/objects/bullet.h \
    game/objects/myobject.h \
    game/objects/npcobject.h \
    game/engine.h \
    game/graphic.h \
    game/gamepanel.h \
    game/objects/wall.h \
    game/objects/rocketbehavior.h \
    game/objects/bot.h \
    game/objects/kamikaze.h \
    menu/singlegame.h \
    menu/windowsmanager.h \
    game/objects/wallbehavior.h \
    game/objects/fatbot.h \
    reader/levelsreader.h \
    game/level.h \
    reader/parser.h

RESOURCES += \
    roof.qrc
