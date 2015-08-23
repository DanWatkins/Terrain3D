import qbs 1.0

StaticLibrary {
    name: "Terrain3D_Lib"
	cpp.cxxLanguageVersion: "c++14"
	cpp.includePaths: [
        "../Src/",
        "../Ext/ValpineBase/Ext",
        "../Ext/ValpineBase/Src"
	]

    Group {
        name: "C++"
        prefix: "Terrain3D/**/"
        files: ["*.cpp", "*.h"]
    }


    Group {
        name: "Resources"
        prefix: "Terrain3D/Resources/**/"
        files: ["*.*"]
    }

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: "Qt.quick" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.opengl" }
    Depends { name: "Qt.openglextensions" }

    Depends { name: "ValpineBase" }
}
