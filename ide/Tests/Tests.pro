QT       += testlib
QT       -= gui

TARGET = Terrain3DTests
CONFIG   += console \
			c++11
CONFIG   -= app_bundle

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

TEMPLATE = app

DESTDIR += ../../Deployment/Bin/

INCLUDEPATH += ../../Src/Library \
				../../Ext/ \
				../../Ext/gtest/inc/

SOURCES += \
    ../../Src/Tests/Main.cpp \
    ../../Src/Tests/Test_WorldTerrainData.cpp \
    ../../Src/Tests/Test_WorldTerrainLightingSlope.cpp \
	../../Src/Tests/Test_WorldTerrainLightMap.cpp \
    ../../Src/Tests/Test_CoreFPSCounter.cpp

unix|win32: LIBS += -L$$OUT_PWD/../../Deployment/Bin/ -lgtest
unix|win32: LIBS += -L$$OUT_PWD/../../Deployment/Bin/ -lTerrain3D

HEADERS += \
    ../../Src/Tests/Main.h
