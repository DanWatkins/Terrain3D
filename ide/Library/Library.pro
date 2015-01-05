TARGET = Terrain3D
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
QT += qml quick

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

INCLUDEPATH += ../../Src/Library \
			../../Ext/

DESTDIR += ../../Deployment/Bin/

unix {
	target.path = /usr/lib
	INSTALLS += target
}

HEADERS += \
    ../../Src/Library/Core/OpenGLQuickItem/RenderThread.h \
    ../../Src/Library/Core/OpenGLQuickItem/TextureNode.h \
    ../../Src/Library/Core/Core.h \
    ../../Src/Library/Core/Helper.h \
    ../../Src/Library/Core/Image.h \
    ../../Src/Library/Core/MD2.h \
    ../../Src/Library/Core/OBJ.h \
    ../../Src/Library/Core/OpenGLFunctions.h \
    ../../Src/Library/Core/OpenGLQuickItem.h \
    ../../Src/Library/Core/Shader.h \
    ../../Src/Library/World/Terrain/Generator/FaultFormation.h \
    ../../Src/Library/World/Terrain/Generator/Generator.h \
    ../../Src/Library/World/Terrain/Lighting/Slope.h \
    ../../Src/Library/World/Terrain/Data.h \
    ../../Src/Library/World/Terrain/HeightMap.h \
    ../../Src/Library/World/Terrain/IndexData.h \
    ../../Src/Library/World/Terrain/LightMap.h \
    ../../Src/Library/World/Terrain/Renderer.h \
    ../../Src/Library/World/Terrain/Utility.h \
    ../../Src/Library/World/Camera.h \
    ../../Src/Library/World/World.h \
    ../../Src/Library/Constants.h \
    ../../Src/Library/Main.h \
    ../../Src/Library/Core/FPSCounter.h

SOURCES += \
    ../../Src/Library/Core/OpenGLQuickItem/OpenGLQuickItem.cpp \
    ../../Src/Library/Core/OpenGLQuickItem/RenderThread.cpp \
    ../../Src/Library/Core/OpenGLQuickItem/TextureNode.cpp \
    ../../Src/Library/Core/Helper.cpp \
    ../../Src/Library/Core/Image.cpp \
    ../../Src/Library/Core/MD2.cpp \
    ../../Src/Library/Core/OBJ.cpp \
    ../../Src/Library/Core/OpenGLFunctions.cpp \
    ../../Src/Library/Core/Shader.cpp \
    ../../Src/Library/World/Terrain/Generator/FaultFormation.cpp \
    ../../Src/Library/World/Terrain/Generator/Generator.cpp \
    ../../Src/Library/World/Terrain/Lighting/Slope.cpp \
    ../../Src/Library/World/Terrain/Data.cpp \
    ../../Src/Library/World/Terrain/HeightMap.cpp \
    ../../Src/Library/World/Terrain/IndexData.cpp \
    ../../Src/Library/World/Terrain/LightMap.cpp \
    ../../Src/Library/World/Terrain/Renderer.cpp \
    ../../Src/Library/World/Terrain/Utility.cpp \
    ../../Src/Library/World/Camera.cpp \
    ../../Src/Library/World/World.cpp \
    ../../Ext/lodepng.cpp \
    ../../Src/Library/Core/FPSCounter.cpp

