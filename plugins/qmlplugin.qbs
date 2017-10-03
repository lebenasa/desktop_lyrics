import qbs
import qbs.FileInfo
import qbs.File

Product {
    property string pluginName: "qmlplugin"
    name: (qbs.buildVariant == "debug") ? pluginName + "d" : pluginName
    type: "dynamiclibrary"
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["core", "quick", "qml"] }

    property string uri: "com.company.module"

    //qbs.installRoot: Qt.quick.qmlPath
//    qbs.installRoot: "C:/Libraries/Labs/qml/"

    cpp.cxxLanguageVersion: "c++11"
    cpp.enableExceptions: true

    Group {
        condition: true
        fileTagsFilter: "dynamiclibrary"
        qbs.install: true
        qbs.installDir: uri.split(".").join("/")
    }

    Group {
        name: "qmldir"
        condition: File.exists(sourceDirectory + "/qmldir")
        prefix: sourceDirectory + "/"
        files: "qmldir"
        qbs.install: true
        qbs.installDir: uri.split(".").join("/")
    }
}
