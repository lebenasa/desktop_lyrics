import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

import com.leben.fileinfo 1.0
import com.leben.editor 1.0

ApplicationWindow {
    id: root
    width: 800
    height: 600
    title: FileInfo.toLocalFile(savePath) === "" ? "Lyrics Editor" :
                                                   "Lyrics Editor - %1".arg(FileInfo.toLocalFile(savePath))
    property alias editor: ui
    property url savePath
    property url track

    Material.theme: Material.Dark
    Material.primary: Material.Blue
    Material.accent: Material.Cyan

    header: ToolBar{
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            ToolButton {
                text: qsTr("\uf0c7")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Save lyrics.\nShortcut: Ctrl+S")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                enabled: acSave.enabled
                onClicked: ui.save()
            }
            ToolButton {
                text: qsTr("\uf0c7")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Save lyrics in different file.\nShortcut: Ctrl+Shift+S")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                onClicked: acSaveAs.activated();

            }
            ToolButton {
                text: qsTr("\uf115")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Open text/lyrics file.\nShortcut: Ctrl+O")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                onClicked: acOpen.activated()
            }
            ToolButton {
                text: qsTr("\uf01a")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Sync this line and move cursor to next line.\nShortcut: F7")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                onClicked: ui.sync_and_next()
            }
            ToolButton {
                text: qsTr("\uf190")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Sync this line.\nShortcut: F5")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                onClicked: ui.sync()
            }
            ToolButton {
                text: qsTr("\uf063")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Move cursor to next line.\nShortcut: F8")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                onClicked: ui.next()
            }
            ToolButton {
                text: qsTr("\uf062")
                font.family: "FontAwesome"
                font.pixelSize: 24
                hoverEnabled: true
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Move cursor to previous line.\nShortcut: F6")
                ToolTip.delay: 500
                ToolTip.timeout: 1000
                onClicked: ui.prev()
            }
            Item { Layout.fillWidth: true }
        }
    }

    LyricsEditorUI {
        id: ui
        anchors.fill: parent
        anchors.leftMargin: 5
        editor.onCursorPositionChanged: engine.processCursorLoc(editor.cursorPosition)

        EditorEngine {
            id: engine
            quickdoc: ui.editor.textDocument
        }

        property int currentLine: engine.currentLine
        property int currentLineStartPos: engine.currentLinePos
        property int nextLineStartPos: engine.nextLinePos

        function sync_and_next() {
            var tag = qsTr("[%1]").arg(app.timestamp());
            ui.editor.insert(ui.currentLineStartPos, tag);
            ui.editor.cursorPosition = ui.nextLineStartPos;
            ui.editor.focus = true;
        }

        function sync() {
            var tag = qsTr("[%1]").arg(app.timestamp());
            ui.editor.insert(ui.currentLineStartPos, tag);
            ui.editor.focus = true;
        }

        function next() {
            ui.editor.cursorPosition = ui.nextLineStartPos;
            ui.editor.focus = true;
        }

        function prev() {
            ui.editor.cursorPosition = engine.lineStartPos(ui.currentLine - 1);
            ui.editor.focus = true;
        }

        function save() {
            app.saveLyrics(ui.editor.text, root.savePath);
            app.lyricsDir = app.lyricsDir;
            if (media.location == root.track)
                app.lyricsFile = root.savePath;
            status.text = qsTr("Saved lyrics to %1").arg(FileInfo.toLocalFile(root.savePath));
        }

        function save_as(path) {
            app.saveLyrics(ui.editor.text, path);
            root.savePath = path;
            app.lyricsDir = app.lyricsDir;
            if (media.location == root.track)
                app.lyricsFile = path;
            status.text = qsTr("Saved lyrics to %1").arg(FileInfo.toLocalFile(path));
        }

        function open(path) {
            if (FileInfo.exists(path)) {
                root.savePath = path;
                ui.editor.text = app.openLyrics(path);
            }
        }
    }

    footer: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            Label {
                id: status
                Layout.maximumWidth: parent.width / 2
                text: ""
                clip: true
                Timer {
                    id: tmStatus
                    interval: 3000
                    repeat: false
                    triggeredOnStart: false
                    onTriggered: status.text = ""
                }
                onTextChanged: {
                    if (text.length > 0)
                        tmStatus.start();
                }
            }
            Item { Layout.fillWidth: true }
            Label {
                text: qsTr("Col: %1 Line: %2 Pos: %3 \t").arg(ui.editor.cursorPosition - ui.currentLineStartPos).
                arg(ui.currentLine).arg(ui.editor.cursorPosition)
                horizontalAlignment: Text.AlignRight
            }
        }
    }

    FileDialog {
        id: dgOpenLyrics
        title: "Open Lyrics"
        folder: app.lyricsDir
        nameFilters: ["Lyrics files (*.lrc *.txt)", "All files (*.*)"]
        selectExisting: true
        onAccepted: ui.open(fileUrl)
    }

    FileDialog {
        id: dgSaveLyrics
        title: "Save Lyrics"
        folder: dgOpenLyrics.folder
        nameFilters: ["Lyrics files (*.lrc)", "Text files (*.txt)", "All files (*.*)"]
        selectExisting: false
        onAccepted: ui.save_as(fileUrl)
    }

    Shortcut {
        id: acSave
        sequence: "Ctrl+S"
        autoRepeat: false
        enabled: root.savePath != ""
        onActivated: ui.save()
    }
    Shortcut {
        id: acSaveAs
        sequence: "Ctrl+Shift+S"
        autoRepeat: false
        onActivated: {
//            dgSaveLyrics.fileUrl = dgOpenLyrics.folder + "/" + media.artist + " - " + media.title + ".lrc";
            dgSaveLyrics.open();
        }
    }
    Shortcut {
        id: acOpen
        sequence: "Ctrl+O"
        autoRepeat: false
        onActivated: dgOpenLyrics.open()
    }

    Shortcut {
        sequence: "F7"
        autoRepeat: false
        onActivated: ui.sync_and_next()
    }
    Shortcut {
        sequence: "F5"
        autoRepeat: false
        onActivated: ui.sync()
    }
    Shortcut {
        sequence: "F8"
        autoRepeat: false
        onActivated: ui.next()
    }
    Shortcut {
        sequence: "F6"
        autoRepeat: false
        onActivated: ui.prev()
    }

    onVisibleChanged: {
        if (visible)
            root.track = media.location;
    }
}
