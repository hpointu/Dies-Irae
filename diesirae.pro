#-------------------------------------------------
#
# Project created by QtCreator 2010-12-05T19:02:45
#
#-------------------------------------------------

QT       += core gui

TARGET = DiesIrae
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Bloc.cpp \
    World.cpp


INCLUDEPATH += /usr/local/include/Box2D
LIBPATH += /usr/local/lib
LIBS += -lBox2D

HEADERS  += MainWindow.h \
    Bloc.h \
    Utils.h \
    World.h

FORMS    += MainWindow.ui
