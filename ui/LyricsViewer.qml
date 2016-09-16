import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import Qt.labs.settings 1.0

LyricsViewerUI {
    id: root
    focus: true
    property bool syncPosition: false
    property Window window

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

    txLyricsFolder.text: dgOpenLyrics.folder

    searchView.delegate: ItemDelegate {
        text: modelData.name
        width: parent.width
        onClicked: app.lyricsFile = modelData.path
    }
    searchView.onModelChanged: {
        if (searchView.model.length > 0 && searchView.model[0].score >= 0.6) {
            app.lyricsFile = searchView.model[0].path;
        }
        else
            app.lyricsFile = "";
    }

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

    Binding {
        target: app
        property: "lyricsDir"
        value: dgOpenLyrics.folder
    }

    Binding {
        target: searchView
        property: "model"
        value: app.search_lyrics(
                   media.artist.length > 0 ? media.artist : media.location,
                   media.title.length > 0 ? media.title : media.location)
    }

    Connections {
        target: media
        onPositionChanged: {
            syncPosition = true;
            mediaPosition.value = media.position / media.mtime;
            syncPosition = false;
        }
    }

    topLayout.onVisibleChanged: {
        window.height += topLayout.visible ? 100 : -100;
    }
    mediaPosition.onVisibleChanged: {
        window.height += mediaPosition.visible ? 100 : -100;
    }
    controlLayout.onVisibleChanged: {
        window.height += controlLayout.visible ? 80 : -80;
    }
    searchView.onVisibleChanged: {
        window.height += searchView.visible ? 200 : -200;
    }
    bottomLayout.onVisibleChanged: {
        window.height += bottomLayout.visible ? 80 : -80;
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_F1)
            topLayout.visible = !topLayout.visible;
        else if (event.key === Qt.Key_F2)
            lyricsArea.visible = !lyricsArea.visible;
        else if (event.key === Qt.Key_F3) {
            mediaPosition.visible = !mediaPosition.visible;
            controlLayout.visible = !controlLayout.visible;
        }
        else if (event.key === Qt.Key_F4) {
            searchView.visible = !searchView.visible;
            bottomLayout.visible = !bottomLayout.visible;
        }
        else if (event.key === Qt.Key_F5)
            app.loadCompactUI();
    }

    Settings {
        property alias lastLyricsFolder: dgOpenLyrics.folder
    }

    Component.onCompleted: {
        searchView.model = app.search_lyrics(
                   media.artist.length > 0 ? media.artist : media.location,
                   media.title.length > 0 ? media.title : media.location);
    }
}
