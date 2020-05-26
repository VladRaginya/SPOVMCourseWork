#-------------------------------------------------
#
# Project created by QtCreator 2020-05-09T17:14:54
#
#-------------------------------------------------

QT       += core gui

TARGET = CourseWork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    baselogic.cpp \
    editstringdialog.cpp \
    editdworddialog.cpp \
    controller.cpp \
    addkeydialog.cpp \
    addvaluedialog.cpp \
    editbinarydialog.cpp \
    editqworddialog.cpp \
    nameexception.cpp \
    typeexception.cpp \
    baseexception.cpp

HEADERS  += mainwindow.h \
    baselogic.h \
    editstringdialog.h \
    editdworddialog.h \
    controller.h \
    addkeydialog.h \
    addvaluedialog.h \
    editbinarydialog.h \
    editqworddialog.h \
    nameexception.h \
    typeexception.h \
    baseexception.h

FORMS    += mainwindow.ui \
    editstringdialog.ui \
    editdworddialog.ui \
    addkeydialog.ui \
    addvaluedialog.ui \
    editbinarydialog.ui \
    editqworddialog.ui

gcc:CXXFLAGS += -std=c++11
