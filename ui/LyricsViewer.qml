import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import Qt.labs.settings 1.0

import com.leben.fileinfo 1.0
import com.leben.appsettings 1.0

LyricsViewerUI {
    id: root
    focus: true
    property bool syncPosition: false
    property bool syncOffset: false
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
    sbOffset.onValueChanged: {
        if (!syncOffset)
            app.offset = sbOffset.value
    }

    txLyricsFolder.text: dgOpenLyrics.folder
    sbOffset.editable: false

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

    Connections {
        target: app
        onOffsetChanged: {
            syncOffset = true;
            sbOffset.value = app.offset;
            syncOffset = false;
        }
        onEditorRequested: {
            app.reloadMainUI();
            editor.editor.open(app.lyricsFile);
            editor.visible = true;
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

    LyricsEditor {
        id: editor
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
        else if (event.key === Qt.Key_F6) {
            editor.editor.open(app.lyricsFile);
            editor.visible = true;
        }
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
