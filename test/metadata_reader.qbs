import qbs

CppApplication {
    Depends { name: "Qt"; submodules: [ "core", "gui", "dbus" ] }

    consoleApplication: true
    cpp.enableExceptions: true
    cpp.cxxLanguageVersion: "c++11"

    files: [
        "../media_service.cpp",
        "../media_service.h",
        "metadata_reader_test.cpp",
    ]
}
