import qbs
import "../qmlplugin.qbs" as QmlPlugin

QmlPlugin {
    name: "appsettings_qmlplugin"
    pluginName: "appsettings_qmlplugin"

    uri: "com.leben.appsettings"

    Depends { name: "Qt"; submodules: "gui" }

    files: [
        "appsettings.h",
        "appsettings.cpp",
        "appsettings_qmlplugin.h",
        "appsettings_qmlplugin.cpp",
    ]
}
