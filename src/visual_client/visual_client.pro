#-------------------------------------------------
#
# Project created by QtCreator 2017-07-01T05:04:01
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visual_client
TEMPLATE = app


SOURCES += main.cpp \
    gamemap.cpp \
    authenticationdialog.cpp \
    clientsocket.cpp \
    mapcell.cpp \
    zappy.cpp \
    error.cpp \
    utils.cpp \
    player.cpp \
    gamemenu.cpp \
    gameend.cpp

HEADERS  += \
    gamemap.h \
    authenticationdialog.h \
    clientsocket.h \
    mapcell.h \
    zappy.h \
    error.h \
    utils.h \
    player.h \
    gamemenu.h \
    gameend.h

RESOURCES += \
    ressources.qrc

FORMS += \
    authenticationdialog.ui
