TEMPLATE = app
TARGET = Terrain3D
QT += qml quick widgets
CONFIG += c++11

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

INCLUDEPATH += ../../Src/Library \
				../../Src/Application \
			../../Ext/

DESTDIR += ../../Bin/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

unix|win32: LIBS += -L$$OUT_PWD/../../Bin/ -lTerrain3D


HEADERS += \
    ../../Src/Application/Main.h \
    ../../Src/Application/Terrain3D.h \
    ../../Src/Application/OpenGLQuickView.h \
    ../../Src/Application/QuickItems/CameraItem.h \
    ../../Src/Application/BackgroundUpdater.h \
    ../../Src/Application/Settings.h \

SOURCES += \
    ../../Src/Application/Main.cpp \
    ../../Src/Application/OpenGLQuickView.cpp \
    ../../Src/Application/Terrain3D.cpp \
    ../../Src/Application/QuickItems/CameraItem.cpp \
    ../../Src/Application/Settings.cpp

OTHER_FILES += \
    ../../Bin/Shaders/camera-frag.glsl \
    ../../Bin/Shaders/camera-vert.glsl \
    ../../Bin/Shaders/sprite-frag.glsl \
    ../../Bin/Shaders/sprite-vert.glsl \
    ../../Bin/Shaders/mesh-obj-frag.glsl \
    ../../Bin/Shaders/mesh-obj-vert.glsl

RESOURCES += \
    ../../Src/Application/qml/main.qrc
