#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T19:14:06
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SlaveMachine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    threadcontrol.cpp \
    socketcontrol.cpp \
    dataprotocol.cpp \
    commandparameter.cpp \
    heartbeatcontrol.cpp \
    collectdata.cpp \
    uploaddata.cpp

HEADERS  += mainwindow.h \
    threadcontrol.h \
    socketcontrol.h \
    dataprotocol.h \
    commandparameter.h \
    heartbeatcontrol.h \
    collectdata.h \
    uploaddata.h

FORMS    += mainwindow.ui
