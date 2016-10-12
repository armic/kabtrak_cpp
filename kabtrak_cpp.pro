#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T10:16:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kabtrak_cpp
TEMPLATE = app


LIBS += "hidapi.dll"
SOURCES += main.cpp\
        kabtrak.cpp \
        tooldraw.cpp \
    globals.cpp

HEADERS  += kabtrak.h \
        cabinet.h \
        tooldraw.h \
    globals.h \
    globalroutines.h \
    hidapi.h \
    hidControl.h

FORMS    += kabtrak.ui
