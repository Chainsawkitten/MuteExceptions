#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T14:42:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MuteExceptions
TEMPLATE = app


SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/AudioSession.cpp

HEADERS  += src/MainWindow.h \
            src/AudioSession.h

FORMS    += src/MainWindow.ui

LIBS += -lole32
CONFIG += c++11
