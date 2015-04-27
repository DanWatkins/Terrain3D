QT       += testlib
QT += qml quick gui
TARGET = Terrain3DTests
CONFIG   += console c++14 c++11
CONFIG   -= app_bundle

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

TEMPLATE = app

DESTDIR += ../../Deployment/Bin/

INCLUDEPATH += ../../Src/Library \
                ../../Ext/ \
                ../../Ext/gtest/inc/ \
                $$(VALPINE_BASE_HOME)/Src/

unix|win32: LIBS += -L$$(VALPINE_BASE_HOME)/Deployment/Bin/ -lgtest
unix|win32: LIBS += -L$$(VALPINE_BASE_HOME)/Deployment/Bin/ -lValpineBase
unix|win32: LIBS += -L$$OUT_PWD/../../Deployment/Bin/ -lTerrain3D

HEADERS += \
    ../../Src/Tests/Tests.h

SOURCES += \
    ../../Src/Tests/Core/Test_Loadable.cpp \
    ../../Src/Tests/Core/Test_OpenGLTaskQueue.cpp \
    ../../Src/Tests/Test_CoreAssetManager.cpp \
    ../../Src/Tests/Test_CoreFPSCounter.cpp \
    ../../Src/Tests/Test_WorldEntityBaseEntity.cpp \
    ../../Src/Tests/Test_WorldEntityManager.cpp \
    ../../Src/Tests/Test_WorldEntityRenderer.cpp \
    ../../Src/Tests/Test_WorldTerrainData.cpp \
    ../../Src/Tests/Test_WorldTerrainLightingSlope.cpp \
    ../../Src/Tests/Test_WorldTerrainLightMap.cpp \
    ../../Src/Tests/Test_WorldTerrainNormalMap.cpp \
    ../../Src/Tests/Test_WorldTerrainRenderer.cpp \
    ../../Src/Tests/Tests.cpp

RESOURCES += \
    ../../Src/Tests/qml/main.qrc

