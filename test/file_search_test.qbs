import qbs

CppApplication {
    Depends { name: "Qt"; submodules: [ "core", "gui", ] }
    
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++11"
    cpp.enableExceptions: true
    cpp.includePaths: "../"
    cpp.cxxFlags: "-Wno-unknown-pragmas"

    files: [
        "../file_search.cpp",
        "../file_search.h",
        "file_search_test.cpp",
        "test_main.cpp",
    ]
}
