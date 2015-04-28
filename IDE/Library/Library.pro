TARGET = Terrain3D
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14 c++11
CONFIG += object_parallel_to_source
QT += qml quick gui

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

INCLUDEPATH += ../../Src/Library \
				../../Ext/ \
				$$(VALPINE_BASE_HOME)/Src/

DESTDIR += ../../Deployment/Bin/

unix {
	target.path = /usr/lib
	INSTALLS += target
}

unix {
	SOURCES += $$system("find ../../Src/Library/ -name '*.cpp'")
	HEADERS += $$system("find ../../Src/Library/ -name '*.h'")
}
win32 {
	SOURCES += $$system("dir ..\..\Src\Library\*.cpp /b /s")
	HEADERS += $$system("dir ..\..\Src\Library\*.h /b /s")
}
