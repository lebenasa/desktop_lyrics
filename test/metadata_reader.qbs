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
    cpp.enableExceptions: true
    cpp.cxxLanguageVersion: "c++11"

    files: [
        "../media_service.cpp",
        "../media_service.h",
        "metadata_reader_test.cpp",
    ]
}
