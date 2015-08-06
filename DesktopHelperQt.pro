#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T10:29:56
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopHelperQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weatherdata.cpp

HEADERS  += mainwindow.h \
    weatherdata.h

FORMS    += mainwindow.ui
