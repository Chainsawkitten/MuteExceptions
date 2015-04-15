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
           src/AudioSession.cpp \
    src/AboutDialog.cpp \
    src/SettingsDialog.cpp

HEADERS  += src/MainWindow.h \
            src/AudioSession.h \
    src/version.h \
    src/AboutDialog.h \
    src/SettingsDialog.h

FORMS    += src/MainWindow.ui \
    src/AboutDialog.ui \
    src/SettingsDialog.ui

LIBS += -lole32
CONFIG += c++11

RESOURCES += resources/resources.qrc
RC_FILE = resources/MuteExceptions.rc
