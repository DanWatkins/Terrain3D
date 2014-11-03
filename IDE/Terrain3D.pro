TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

QMAKE_CFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

INCLUDEPATH += ../Src/ \
			../Ext/

DESTDIR += ../Bin/

SOURCES += \
    ../Src/Core/Font.cpp \
    ../Src/Core/Helper.cpp \
    ../Src/Core/Image.cpp \
    ../Src/Core/MatrixStack.cpp \
    ../Src/Core/OpenGLFunctions.cpp \
    ../Src/Core/OpenGLWindow.cpp \
    ../Src/Core/Shader.cpp \
    ../Src/Core/Sprite.cpp \
    ../Src/Core/SpriteSheet.cpp \
    ../Src/World/Terrain/HeightMap.cpp \
    ../Src/World/Terrain/IndexData.cpp \
    ../Src/World/Terrain/TerrainData.cpp \
    ../Src/World/Terrain/TerrainGenerator.cpp \
    ../Src/World/Terrain/TerrainRenderer.cpp \
    ../Src/World/Terrain/Utility.cpp \
    ../Src/World/Camera.cpp \
    ../Src/World/World.cpp \
    ../Src/Main.cpp \
    ../Src/Terrian3D.cpp \
    ../Ext/lodepng.cpp


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ../Src/Core/Core.h \
    ../Src/Core/Font.h \
    ../Src/Core/Helper.h \
    ../Src/Core/Image.h \
    ../Src/Core/MatrixStack.h \
    ../Src/Core/OpenGLFunctions.h \
    ../Src/Core/OpenGLWindow.h \
    ../Src/Core/Shader.h \
    ../Src/Core/Sprite.h \
    ../Src/Core/SpriteSheet.h \
    ../Src/World/Terrain/HeightMap.h \
    ../Src/World/Terrain/IndexData.h \
    ../Src/World/Terrain/Utility.h \
    ../Src/World/Camera.h \
    ../Src/World/TerrainData.h \
    ../Src/World/TerrainGenerator.h \
    ../Src/World/TerrainRenderer.h \
    ../Src/World/World.h \
    ../Src/Constants.h \
    ../Src/Main.h \
    ../Src/Terrain3D.h \
    ../Ext/lodepng.h

OTHER_FILES += \
    ../Bin/Shaders/camera-frag.glsl \
    ../Bin/Shaders/camera-vert.glsl \
    ../Bin/Shaders/sprite-frag.glsl \
    ../Bin/Shaders/sprite-vert.glsl
