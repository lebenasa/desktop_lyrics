import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick.Controls.Material 2.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true

    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    LyricsViewer {
        id: lyricsView
        anchors.fill: parent
        focus: true
        window: root
    }

    Connections {
        target: app
        onReloadMainUI: root.visible = true
    }

    Settings {
        category: "MainWindow"
        property alias width: root.width
        property alias height: root.height
        property alias x: root.x
        property alias y: root.y
        property alias visibility: root.visibility
    }
}
