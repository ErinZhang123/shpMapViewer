#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T22:09:34
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keke
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    shapelib/shptree.cpp \
    shapelib/shpopen.cpp \
    shapelib/dbfopen.cpp \
    zalshape.cpp \
    point.cpp \
    polyline.cpp \
    polygon.cpp \
    zalshapes.cpp \
    abstractshapefactory.cpp \
    esrishapefactory.cpp \
    assistant.cpp \
    ShapesView.cpp \
    DockWidget.cpp

HEADERS  += mainwindow.h \
    shapelib/shapefil.h \
    zalshape.h \
    point.h \
    polyline.h \
    polygon.h \
    zalshapes.h \
    abstractshapefactory.h \
    esrishapefactory.h \
    assistant.h \
    ShapesView.h \
    DockWidget.h

FORMS    += mainwindow.ui \
    ShapesView.ui \
    DockWidget.ui
