import qbs 1.0

Application {
    name: "Terrain3D_Tests"

    cpp.cxxLanguageVersion: "c++14"
    cpp.includePaths: [
        "../Ext/ValpineBase/Src",
        "../Ext/ValpineBase/Ext",
        "../Src/"
    ]


    files: "Tests.cpp"
//    TODO use custom test thing

//    Group {
//        name: "C++"
//        prefix: "**/"
//        files: ["*.cpp", "*.h"]
//    }


//    Group {
//        name: "Resources"
//        prefix: "Resources/**/"
//        files: ["*.*"]
//    }

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
