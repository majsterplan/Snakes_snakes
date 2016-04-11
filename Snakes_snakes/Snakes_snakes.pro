#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T21:17:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snakes_snakes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filemanager.cpp \
    file.cpp \
    algorithmfile.cpp \
    seriesfile.cpp \
    datamanager.cpp \
    series.cpp \
    algorithm.cpp \
    ifile.cpp \
    point.cpp \
    iinterpreter.cpp \
    pythoninterpreter.cpp

HEADERS  += mainwindow.h \
    filemanager.h \
    file.h \
    algorithmfile.h \
    seriesfile.h \
    datamanager.h \
    series.h \
    algorithm.h \
    ifile.h \
    point.h \
    iinterpreter.h \
    pythoninterpreter.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/python2.7/
INCLUDEPATH += /usr/include/

LIBS += -lpython2.7 -lboost_system -lboost_python
