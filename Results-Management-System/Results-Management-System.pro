#-------------------------------------------------
#
# Project created by QtCreator 2016-06-11T16:28:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Results-Management-System
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    course.cpp \
    person.cpp \
    system.cpp

HEADERS  += mainwindow.h \
    course.hpp \
    global.h \
    person.hpp \
    system.hpp

FORMS    += mainwindow.ui
