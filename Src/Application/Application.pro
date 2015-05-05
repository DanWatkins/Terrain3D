#--General
TEMPLATE = app
TARGET = Terrain3D
CONFIG += c++14 c++11
QT += gui qml quick opengl openglextensions

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas


#--Compile Sources
unix {
	SOURCES += $$system("find . -name '*.cpp'")
	HEADERS += $$system("find . -name '*.h'")
}
win32 {
	SOURCES += $$system("dir .\*.cpp /b /s")
	HEADERS += $$system("dir .\*.h /b /s")
}

RESOURCES += ../../Src/Application/qml/main.qrc


#--Dependencies
INCLUDEPATH += ../Library \
				../Application \
				../../Ext/ValpineBase/Src/ \
				../../Ext/ValpineBase/Ext/

Release: CONFIG_DIR = release
Debug: CONFIG_DIR = debug

LIBS += -L../../Ext/ValpineBase/Src/ValpineBase/$$CONFIG_DIR/ -lValpineBase
LIBS += -L../Library/$$CONFIG_DIR/ -lTerrain3D

PRE_TARGETDEPS += ../../Ext/ValpineBase/Src/ValpineBase/$$CONFIG_DIR/libValpineBase.a \
					../Library/$$CONFIG_DIR/libTerrain3D.a
