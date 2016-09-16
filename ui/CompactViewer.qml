import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

import Qt.labs.settings 1.0

import com.leben.lyrics 1.0

LyricsWindow {
    id: root
    width: 800
    height: 30
    visible: true

    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    Item {
        anchors.fill: parent

        Pane {
            anchors.fill: parent
            focus: true
            Label {
                anchors.fill: parent
                text: app.currentLine
                font.pointSize: 12
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
            }

            Keys.onPressed: {
                if (event.key === Qt.Key_F5)
                    app.reloadMainUI();
            }
        }

        MouseArea {
            anchors {
                top: parent.top; bottom: parent.bottom
                left: parent.left
            }
            width: 5
            cursorShape: Qt.SizeHorCursor
        }
        MouseArea {
            anchors {
                top: parent.top; bottom: parent.bottom
                right: parent.right
            }
            width: 5
            cursorShape: Qt.SizeHorCursor
        }
        MouseArea {
            anchors {
                left: parent.left; right: parent.right;
                rightMargin: 5; leftMargin: 5
                top: parent.top
            }
            height: 5
            cursorShape: Qt.SizeVerCursor
        }
        MouseArea {
            anchors {
                left: parent.left; right: parent.right;
                rightMargin: 5; leftMargin: 5
                bottom: parent.bottom
            }
            height: 5
            cursorShape: Qt.SizeVerCursor
        }
    }

    Connections {
        target: app
        onReloadCompactUI: root.visible = true
    }

    Settings {
        category: "CompactWindow"
        property alias x: root.x
        property alias y: root.y
    }
}
