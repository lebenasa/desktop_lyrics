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

Project {
    name: "desktop_lyrics_project"
    CppApplication {
        name: "desktop_lyrics"
        Depends { name: "Qt"; submodules: [ "core", "quick", "quickcontrols2", "gui", "dbus", "widgets" ] }
        Depends { name: "appsettings_qmlplugin"}
        Depends { name: "fileinfo_qmlplugin"}

        cpp.cxxLanguageVersion: "c++14"
        cpp.enableExceptions: true
        cpp.includePaths: ["/usr/include/nvidia-361/"]
        consoleApplication: false

        files: [
            "src/desktop_lyrics.cpp",
            "src/desktop_lyrics.h",
            "src/lyrics_editor.cpp",
            "src/lyrics_editor.h",
            "src/lyrics_parser.cpp",
            "src/lyrics_parser.h",
            "src/lyrics_window.cpp",
            "src/lyrics_window.h",
            "src/media_service.cpp",
            "src/media_service.h",
            "src/file_search.h",
            "src/file_search.cpp",
            "desktop_lyrics.qrc",
            "main.cpp",
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

    references: [
        "plugins/appsettings_qmlplugin/appsettings_qmlplugin.qbs",
        "plugins/fileinfo_qmlplugin/fileinfo_qmlplugin.qbs",
    ]
}
