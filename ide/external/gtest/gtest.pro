#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T21:26:44
#
#-------------------------------------------------

QT       -= core gui

TARGET = gtest
TEMPLATE = lib

CONFIG += c++11

INCLUDEPATH += ../../../Ext/gtest/inc/ \
				../../../Ext/gtest/

DEFINES += GTEST_LIBRARY
DESTDIR += ../../../Bin/

SOURCES += \
	../../../Ext/gtest/src/gtest-all.cc

unix {
    target.path = /usr/lib
    INSTALLS += target
}
