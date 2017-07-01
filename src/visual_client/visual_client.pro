#-------------------------------------------------
#
# Project created by QtCreator 2017-07-01T05:04:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visual_client
TEMPLATE = app


SOURCES += main.cpp \
    gamemap.cpp \
    authenticationdialog.cpp

HEADERS  += \
    gamemap.h \
    authenticationdialog.h

RESOURCES += \
    ressources.qrc

FORMS += \
    authenticationdialog.ui
