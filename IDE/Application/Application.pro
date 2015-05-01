TEMPLATE = app
TARGET = Terrain3D
QT += gui qml quick
CONFIG += c++14 c++11

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

INCLUDEPATH += ../../Src/Library \
                ../../Src/Application \
                ../../Ext/ \
                $$(VALPINE_BASE_HOME)/Src/


unix {
	SOURCES += $$system("find ../../Src/Application/ -name '*.cpp'")
	HEADERS += $$system("find ../../Src/Application/ -name '*.h'")
}
win32 {
	SOURCES += $$system("dir ..\..\Src\Application\*.cpp /b /s")
	HEADERS += $$system("dir ..\..\Src\Application\*.h /b /s")
}

RESOURCES += \
    ../../Src/Application/qml/main.qrc


debug: CONFIG_DIR = debugs
release: CONFIG_DIR = release

LIBS += -L../Library/$$CONFIG_DIR/ -lValpineBase
LIBS += -L../Library/$$CONFIG_DIR/ -lTerrain3D
