import qbs

CppApplication {
    Depends { name: "Qt"; submodules: [ "core", "gui", "sql" ] }
    
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++11"
    cpp.enableExceptions: true
    cpp.includePaths: "../"
    cpp.cxxFlags: "-Wno-unknown-pragmas"

    files: [
        "database_test.cpp",
        "test_main.cpp",
    ]

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

}
