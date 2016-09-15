import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    width: 800
    height: 600
    property alias lbGenre: lbGenre
    property alias lbAlbum: lbAlbum
    property alias lbArtist: lbArtist
    property alias lbTitle: lbTitle
    property alias mediaInfoR: mediaInfoR
    property alias btnPause: btnPause
    property alias mediaPosition: mediaPosition
    property alias mediaArt: mediaArt
    property alias btnPrev: btnPrev
    property alias btnPlay: btnPlay
    property alias btnStop: btnStop
    property alias btnNext: btnNext
    property alias btnOpenLyrics: btnOpenLyrics
    property alias lyricsArea: lyricsArea

    ColumnLayout {
        id: columnLayout1
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent


        GridLayout {
            id: gridLayout1
            Layout.maximumHeight: 200
            columns: 3
            Layout.preferredHeight: 200
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Image {
                id: mediaArt
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                sourceSize.width: 120
                fillMode: Image.PreserveAspectFit
                source: "/tmp/clementine-art-r18373.jpg"
            }
            GridLayout {
                id: mediaInfoLayout
                columns: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 2

                Label {
                    id: lbTitle
                    text: qsTr("Title")
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 15
                    font.bold: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                Label {
                    id: mediaInfoR
                    text: qsTr("")
                    Layout.fillWidth: false
                    Layout.fillHeight: true
                }

                Label {
                    id: lbArtist
                    text: qsTr("Artist")
                    font.bold: true
                    font.pointSize: 12
                    Layout.fillWidth: true
                }

                Label {
                    id: label3
                    text: qsTr("")
                }

                Label {
                    id: lbAlbum
                    text: qsTr("Album")
                    Layout.fillWidth: true
                }

                Label {
                    id: label5
                    text: qsTr("")
                }

                Label {
                    id: lbGenre
                    text: qsTr("Genre")
                    Layout.fillWidth: true
                }

                Label {
                    id: label7
                    text: qsTr("")
                }
            }
            Slider {
                id: mediaPosition
                Layout.preferredHeight: 30
                Layout.fillWidth: true
                Layout.columnSpan: 3
                value: 0.5
            }
            RowLayout {
                id: rowLayout1
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                Layout.columnSpan: 3








                Item {
                    id: item1
                    Layout.fillWidth: true
                }
                Button {
                    id: btnPrev
                    text: qsTr("Prev")
                }
                Button {
                    id: btnPlay
                    text: qsTr("Play")
                }
                Button {
                    id: btnPause
                    text: qsTr("Pause")
                }
                Button {
                    id: btnStop
                    text: qsTr("Stop")
                }
                Button {
                    id: btnNext
                    text: qsTr("Next")
                }
                Item {
                    id: item2
                    Layout.fillWidth: true
                }
                Button {
                    id: btnOpenLyrics
                    text: qsTr("Open Lyrics")
                }
            }
        }

        Label {
            id: lyricsArea
            text: qsTr("Lyrics")
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
