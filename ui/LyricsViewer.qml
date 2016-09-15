import QtQuick 2.4
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

LyricsViewerUI {
    id: root
    property bool syncPosition: false

    btnPrev.onClicked: media.prev()
    btnPlay.onClicked: media.play()
    btnPause.onClicked: media.pause()
    btnStop.onClicked: media.stop()
    btnNext.onClicked: media.next()
    mediaPosition.onValueChanged: {
        if (!syncPosition)
            media.position = mediaPosition.value * media.mtime;
    }
    btnOpenLyrics.onClicked: dgOpenLyrics.open()

    FileDialog {
        id: dgOpenLyrics
        title: "Open Lyrics File"
        folder: shortcuts.home
        nameFilters: [ "Lyrics files (*.lrc *.txt)", "All files (*.*)" ]
        selectExisting: true
        selectMultiple: false
        onAccepted: app.lyricsFile = fileUrl
    }

    Binding {
        target: mediaArt
        property: "source"
        value: media.arturl
    }

    Binding {
        target: lbTitle
        property: "text"
        value: media.title
    }

    Binding {
        target: lbAlbum
        property: "text"
        value: media.album
    }

    Binding {
        target: lbArtist
        property: "text"
        value: media.artist
    }

    Binding {
        target: lbGenre
        property: "text"
        value: media.genre
    }

    Binding {
        target: lyricsArea
        property: "text"
        value: app.currentLine
    }

    Connections {
        target: media
        onPositionChanged: {
            syncPosition = true;
            mediaPosition.value = media.position / media.mtime;
            syncPosition = false;
        }
    }

    Settings {
        property alias lastLyricsFolder: dgOpenLyrics.folder
    }
}
