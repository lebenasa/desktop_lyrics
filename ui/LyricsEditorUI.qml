import QtQuick 2.7
import QtQuick.Controls 2.0

Flickable {
    id: root
    width: 800
    height: 600
    property alias editor: lyricsEdit

    TextArea.flickable: TextArea {
        id: lyricsEdit
    }

    ScrollBar.vertical: ScrollBar{ id: vscroll }
    ScrollBar.horizontal: ScrollBar{ }
}
