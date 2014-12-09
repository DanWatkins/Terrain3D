QT       += testlib
QT       -= gui

TARGET = Terrain3DTests
CONFIG   += console \
			c++11
CONFIG   -= app_bundle

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

TEMPLATE = app

DESTDIR += ../../Bin/
INCLUDEPATH += ../../Src/Library \
				../../Ext/ \
				../../Ext/gtest/inc/

DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix|win32: LIBS += -L$$OUT_PWD/../../Bin/ -lTerrain3D
unix|win32: LIBS += -L$$OUT_PWD/../External/gtest/ -lgtest

SOURCES += \
    ../../Src/Tests/Main.cpp \
    ../../Src/Tests/Test_WorldTerrainData.cpp \
    ../../Src/Tests/Test_WorldTerrainLightingSlope.cpp \
	../../Src/Tests/Test_WorldTerrainLightMap.cpp


