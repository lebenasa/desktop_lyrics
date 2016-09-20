# Lyrics Widget and Editor for Desktop

I really like singing (though that is not to say that my voice is any good).
I especially like to sing while working on PC, it helps to keep me motivated.

MiniLyrics from Crintsoft is particularly great for me, it has a single bar
mode which doesn't distract me and a huge collection of lyrics.
Unfortunately I hardly use Windows to work anymore, and I can't find MiniLyrics
for Linux.
Using Wine simply does not feel right, therefore I decided to spend a week
working on a working MiniLyrics replacement for Linux.
Since I used Qt, the app would be, in theory, able to work in other desktop 
platforms.

Unlike MiniLyrics, this app does not have an auto-scroll lyrics mode.
It also can't search lyrics online, I can't find free and legal web API for 
that purpose, you would have to search the lyrics and sync it by yourself
(or run MiniLyrics in Wine and search the lyrics there).

## Requirements
For running the app, you would need:
1. Clementine, for actually playing musics. Other players are not supported yet.
2. Qt libraries >= 5.7.0

For building the app, you would need:
1. Qt >= 5.7.0
2. Qt Build System (`qbs`, included with Qt)
2. Catch, for testing (included as submodule)

It used the new `QtQuick.Controls 2.0` module so older version of Qt probably won't work.

## Usage Guide
Before using the app, I'd recommend you to copy your lyrics to a path which is easily
reachable from Linux.
Personally, I'd create a symbolic link to my MiniLyrics folder in home directory so
new lyrics from MiniLyrics are instantly available in Linux.

After starting the app, you'd find two main windows, the big one has simple media controls 
and a list of available lyrics to pick from, the small one always stays on top to display 
one line of lyrics.
If you close either window, press **F5** in the remaining window to summon the closed window.

![Desktop Lyrics UI in Linux Mint](./desktop_lyrics_both.png)

If you find correct lyrics from suggestion box just click it, otherwise open the lyrics
file manually by clicking the big *Browse Lyrics* button.
Notice that manually loading lyrics file would change the app's lyrics directory, so
it'd be better if you copy that file to a dedicated lyrics directory.

If you don't have the correct lyrics file, you can create one.
Just press **F6** to call the Lyrics Editor, put the correct lyrics there and
begin timing each line to currently playing song's timing.
The editor is not as advanced as MiniLyrics', but the workflow is similar.
The text doesn't change when the track is changing, and media control is still available
during lyrics timing so you can try several times to get the timing right.

![The Lyrics Editor](./lyrics_editor.png)

## Under the Hood
The app uses DBus to communicate with Clementine, therefore you can simply rewrite that
DBus logic to make it works with your favorite music player.
The DBus logic can be found in [media_service.h](./media_service.h) and 
[media_service.cpp](./media_service.cpp).

## Additional Features and Bug Fixes
Since this is a one week side-project and it already fits my need, I don't think I would
work on additional features anytime soon.
What I think can be improved are:
- More complete UI, with proper icons, shortcuts, and tooltips
- Resizeable CompactViewer
- Proper window event handling in CompactViewer
- Context menus, although this one is a bit tricky
- Better lyrics suggestion algorithm
- Persistent offset settings

Contributions are welcome :).

