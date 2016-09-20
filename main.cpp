#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "media_service.h"
#include "desktop_lyrics.h"
#include "lyrics_window.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app{ argc, argv };

    qmlRegisterType<LyricsWindow>("com.leben.lyrics", 1, 0, "LyricsWindow");
    qmlRegisterType<EditorEngine>("com.leben.editor", 1, 0, "EditorEngine");

    QQuickStyle::setStyle("Material");

    MediaService service;
    AppEngine lrcapp;
    lrcapp.setMedia(&service);

    lrcapp.loadMainUI();
    lrcapp.loadCompactUI();

    return app.exec();
}
