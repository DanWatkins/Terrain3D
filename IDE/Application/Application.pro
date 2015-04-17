TEMPLATE = app
TARGET = Terrain3D
QT += qml quick
CONFIG += c++11

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

INCLUDEPATH += ../../Src/Application \
				../../Src/Library \
				../../Ext/

DESTDIR = ../../Deployment/Bin/

unix|win32: LIBS += -L$$OUT_PWD/../../Deployment/Bin/ -lTerrain3D

HEADERS += \
    ../../Src/Application/QuickItems/CameraItem.h \
    ../../Src/Application/Application.h \
    ../../Src/Application/BackgroundUpdater.h \
    ../../Src/Application/OpenGLQuickView.h \
    ../../Src/Application/Settings.h \
    ../../Src/Application/Terrain3D.h

SOURCES += \
    ../../Src/Application/QuickItems/CameraItem.cpp \
    ../../Src/Application/Application.cpp \
    ../../Src/Application/OpenGLQuickView.cpp \
    ../../Src/Application/Settings.cpp \
    ../../Src/Application/Terrain3D.cpp

RESOURCES += \
    ../../Src/Application/qml/main.qrc

