import QtQuick 2.4
import QtQuick.Controls 2.0

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true

    LyricsViewer {
        id: lyrics_view
        anchors.fill: parent
    }
}
