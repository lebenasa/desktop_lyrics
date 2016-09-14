import qbs

CppApplication {
    Depends { name: "Qt"; submodules: [ "core", "gui", "dbus" ] }
    
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++11"
    cpp.enableExceptions: true
    cpp.includePaths: "../"
    cpp.cxxFlags: "-Wno-unknown-pragmas"

    files: [
        "../media_service.h",
        "../media_service.cpp",
        "../lyrics_parser.h",
        "../lyrics_parser.cpp",
        "lyrics_parser_test.cpp",
        "test_main.cpp",
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

    Group {
        name: "Lyrics File"
        files: [
            "YUI - Good-bye Days.lrc"
        ]
        qbs.install: true
    }
}
