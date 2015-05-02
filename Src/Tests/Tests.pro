QT       += testlib
QT += qml quick gui
TARGET = Terrain3DTests
CONFIG   += console c++14 c++11
CONFIG   -= app_bundle

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

TEMPLATE = app

INCLUDEPATH += ../Library \
				../../Ext/ValpineBase/Ext/ \
				../../Ext/ValpineBase/Ext/gmock/gtest/include/ \
				../../Ext/ValpineBase/Src/

unix {
	SOURCES += $$system("find ../../Src/Tests/ -name '*.cpp'")
	HEADERS += $$system("find ../../Src/Tests/ -name '*.h'")
}
win32 {
	SOURCES += $$system("dir ..\..\Src\Tests\*.cpp /b /s")
	HEADERS += $$system("dir ..\..\Src\Tests\*.h /b /s")
}

RESOURCES += \
	../../Src/Tests/qml/main.qrc



Release: CONFIG_DIR = release
Debug: CONFIG_DIR = debug

LIBS += -L../../Ext/ValpineBase/Src/ValpineBase/$$CONFIG_DIR/ -lValpineBase
LIBS += -L../../Ext/ValpineBase/Src/External/gtest/$$CONFIG_DIR/ -lgtest
LIBS += -L../Library/$$CONFIG_DIR/ -lTerrain3D

PRE_TARGETDEPS += ../../Ext/ValpineBase/Src/ValpineBase/$$CONFIG_DIR/libValpineBase.a \
					../../Ext/ValpineBase/Src/External/gtest/$$CONFIG_DIR/libgtest.a \
					../Library/$$CONFIG_DIR/libTerrain3D.a


