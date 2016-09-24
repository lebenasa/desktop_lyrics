import QtQuick 2.7
import QtQuick.Controls 2.0

Flickable {
    id: root
    width: 800
    height: 600
    interactive: false
    property alias editor: lyricsEdit

    TextArea.flickable: TextArea {
        id: lyricsEdit
        selectByMouse: true

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            onWheel: {
                if (wheel.angleDelta.y > 0)
                    vscroll.decrease();
                else
                    vscroll.increase();
            }
        }
    }

    ScrollBar.vertical: ScrollBar{ id: vscroll }
    ScrollBar.horizontal: ScrollBar{ }
}
