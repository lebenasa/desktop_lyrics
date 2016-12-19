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
    name: "desktop_lyrics"
    Depends { name: "Qt"; submodules: [ "core", "quick", "quickcontrols2", "gui", "dbus", "widgets" ] }

    cpp.cxxLanguageVersion: "c++14"
    cpp.enableExceptions: true
    cpp.includePaths: ["/usr/include/nvidia-361/"]
    consoleApplication: false

    files: [
        "desktop_lyrics.cpp",
        "desktop_lyrics.h",
        "desktop_lyrics.qrc",
        "lyrics_parser.cpp",
        "lyrics_parser.h",
        "lyrics_window.cpp",
        "lyrics_window.h",
        "main.cpp",
        "media_service.cpp",
        "media_service.h",
        "file_search.h",
        "file_search.cpp",
    ]

//    qbs.installRoot: "/home/leben/bin/"

    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

    Group {
        files: [
            "ui/CompactViewer.qml",
            "ui/LyricsEditor.qml",
            "ui/LyricsEditorUI.qml",
            "ui/LyricsViewer.qml",
            "ui/LyricsViewerUI.ui.qml",
            "ui/main.qml",
        ]
        name: "QML Files"
        qbs.install: true
        qbs.installDir: "ui/"
    }
}
