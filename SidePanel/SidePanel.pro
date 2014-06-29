#-------------------------------------------------
#
# Project created by QtCreator 2014-05-27T13:21:27
#
#-------------------------------------------------

QT       += widgets

TARGET = SidePanel
TEMPLATE = lib

DESTDIR = $$PWD/../lib/
CONFIG += c++11

DEFINES += SIDEPANEL_LIBRARY

SOURCES += side_panel.cpp \
    splitter_handle.cpp \
    collapsible_splitter.cpp \
    side_bar.cpp

HEADERS += side_panel.h\
        sidepanel_global.h \
    splitter_handle.h \
    collapsible_splitter.h \
    side_bar.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

