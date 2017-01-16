import qbs
import "../qmlplugin.qbs" as QmlPlugin

QmlPlugin {
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
