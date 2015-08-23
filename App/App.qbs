import qbs 1.0

Application {
    name: "Terrain3D"

	cpp.cxxLanguageVersion: "c++14"
	cpp.includePaths: [
        "../Src/",
        "../Ext/ValpineBase/Ext",
		"../Ext/ValpineBase/Src"
	]

    Group {
        name: "C++"
        prefix: "**/"
        files: ["*.cpp", "*.h"]
    }


    Group {
        name: "Resources"
        prefix: "**/"
        files: ["*.qml*", "*.qrc"]
    }

	Depends { name: "cpp" }
	Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
	Depends { name: "Qt.quick" }
    Depends { name: "Qt.widgets" }
    Depends { name: "Qt.opengl" }
    Depends { name: "Qt.openglextensions" }

    Depends { name: "ValpineBase" }
    Depends { name: "Terrain3D_Lib" }
}
