TARGET = Terrain3D
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14
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

HEADERS += \
    ../../Src/Library/Core/Asset/private/FaceData.h \
    ../../Src/Library/Core/Asset/private/MaterialData.h \
    ../../Src/Library/Core/Asset/private/MeshPrivate.h \
    ../../Src/Library/Core/Asset/private/OBJ.h \
    ../../Src/Library/Core/Asset/private/SubMesh.h \
    ../../Src/Library/Core/Asset/Manager.h \
    ../../Src/Library/Core/Asset/Mesh.h \
    ../../Src/Library/Core/Core.h \
    ../../Src/Library/Core/FPSCounter.h \
    ../../Src/Library/Core/Helper.h \
    ../../Src/Library/Core/Loadable.h \
    ../../Src/Library/Core/MutexTryLocker.h \
    ../../Src/Library/Core/OpenGLFunctions.h \
    ../../Src/Library/Core/OpenGLTaskQueue.h \
    ../../Src/Library/Core/ShaderProgram.h \
    ../../Src/Library/World/Entity/BaseEntity.h \
    ../../Src/Library/World/Entity/Component.h \
    ../../Src/Library/World/Entity/Manager.h \
    ../../Src/Library/World/Entity/RenderComponent.h \
    ../../Src/Library/World/Entity/Renderer.h \
    ../../Src/Library/World/Terrain/Generator/FaultFormation.h \
    ../../Src/Library/World/Terrain/Generator/Generator.h \
    ../../Src/Library/World/Terrain/Lighting/Slope.h \
    ../../Src/Library/World/Terrain/Water/Renderer.h \
    ../../Src/Library/World/Terrain/Data.h \
    ../../Src/Library/World/Terrain/HeightMap.h \
    ../../Src/Library/World/Terrain/LightMap.h \
    ../../Src/Library/World/Terrain/NormalMap.h \
    ../../Src/Library/World/Terrain/Renderer.h \
    ../../Src/Library/World/Terrain/Utility.h \
    ../../Src/Library/World/Camera.h \
    ../../Src/Library/World/Environment.h \
    ../../Src/Library/Constants.h \
    ../../Src/Library/Library.h

SOURCES += \
    ../../Src/Library/Core/Asset/private/FaceData.cpp \
    ../../Src/Library/Core/Asset/private/MaterialData.cpp \
    ../../Src/Library/Core/Asset/private/MeshPrivate.cpp \
    ../../Src/Library/Core/Asset/private/OBJ.cpp \
    ../../Src/Library/Core/Asset/private/SubMesh.cpp \
    ../../Src/Library/Core/Asset/Manager.cpp \
    ../../Src/Library/Core/Asset/Mesh.cpp \
    ../../Src/Library/Core/FPSCounter.cpp \
    ../../Src/Library/Core/Helper.cpp \
    ../../Src/Library/Core/OpenGLFunctions.cpp \
    ../../Src/Library/Core/OpenGLTaskQueue.cpp \
    ../../Src/Library/Core/ShaderProgram.cpp \
    ../../Src/Library/World/Entity/BaseEntity.cpp \
    ../../Src/Library/World/Entity/Manager.cpp \
    ../../Src/Library/World/Entity/RenderComponent.cpp \
    ../../Src/Library/World/Entity/Renderer.cpp \
    ../../Src/Library/World/Terrain/Generator/FaultFormation.cpp \
    ../../Src/Library/World/Terrain/Generator/Generator.cpp \
    ../../Src/Library/World/Terrain/Lighting/Slope.cpp \
    ../../Src/Library/World/Terrain/Water/Renderer.cpp \
    ../../Src/Library/World/Terrain/Data.cpp \
    ../../Src/Library/World/Terrain/HeightMap.cpp \
    ../../Src/Library/World/Terrain/LightMap.cpp \
    ../../Src/Library/World/Terrain/NormalMap.cpp \
    ../../Src/Library/World/Terrain/Renderer.cpp \
    ../../Src/Library/World/Terrain/Utility.cpp \
    ../../Src/Library/World/Camera.cpp \
    ../../Src/Library/World/Environment.cpp

