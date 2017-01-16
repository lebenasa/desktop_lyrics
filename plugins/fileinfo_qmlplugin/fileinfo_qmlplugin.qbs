import qbs 1.0
import qbs.FileInfo
import "../qmlplugin.qbs" as QmlPlugin

QmlPlugin {
    pluginName: "fileinfo_qmlplugin"

    uri: "com.leben.fileinfo"

    files: [
        "fileinfo_qmlplugin_plugin.h",
        "fileinfo.h",
        "fileinfo_qmlplugin_plugin.cpp",
        "fileinfo.cpp",
    ]
}
