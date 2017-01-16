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
    Depends { name: "Qt"; submodules: [ "core", "gui", ] }
    
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++11"
    cpp.enableExceptions: true
    cpp.includePaths: "../3rdparty"
    cpp.cxxFlags: "-Wno-unknown-pragmas"

    files: [
        "../src/file_search.cpp",
        "../src/file_search.h",
        "file_search_test.cpp",
        "test_main.cpp",
    ]
}
