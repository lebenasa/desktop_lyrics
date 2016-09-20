/*  
 *  COPYRIGHT (c) 2015 Leben Asa. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
