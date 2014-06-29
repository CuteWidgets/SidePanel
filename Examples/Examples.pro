#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T09:02:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Examples
TEMPLATE = app

CONFIG += c++11
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/ -lSidePanel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/ -lSidePanel
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lSidePanel

INCLUDEPATH += $$PWD/../SidePanel
DEPENDPATH += $$PWD/../SidePanel

RESOURCES += \
    resources.qrc
