import qbs

CppApplication {
    name: "Desktop Lyrics"
    Depends { name: "Qt"; submodules: [ "core", "quick", "gui", "dbus" ] }
}
