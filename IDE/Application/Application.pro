TEMPLATE = app
TARGET = Terrain3D
QT += qml quick
CONFIG += c++11

INCLUDEPATH += ../../Src/

DESTDIR = ../../Bin/
MOC_DIR = ../../_intermediate/Moc/
OBJECTS_DIR = ../../_intermediate/Obj/

unix|win32: LIBS += -L$$OUT_PWD/../../Bin/ -lLibrary

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

