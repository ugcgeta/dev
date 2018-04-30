#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T07:21:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camera
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# add for opencv
DEPENDPATH += /usr/local/include
INCLUDEPATH +=  /usr/local/include
LIBS += `pkg-config --libs opencv`
