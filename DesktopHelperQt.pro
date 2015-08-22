#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T10:29:56
#
#-------------------------------------------------

QT       += core gui xml network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += warn_off
TARGET = DesktopHelperQt
TEMPLATE = app


SOURCES += main.cpp\
    base.cpp \
    mainwindow.cpp \
    weatherdata.cpp

HEADERS  += mainwindow.h \
    weatherdata.h \
    base.h \

FORMS    += mainwindow.ui

DISTFILES += \
    .gitignore \
    DesktopHelperQt.pro.user \
    DesktopHelperQt.pro.user.7c9bc3e \
    LICENSE \
    README.md \
    Dockerfile

RESOURCES += \
    resources.qrc

RESOURCES += \
    images.qrc

