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

    QQuickStyle::setStyle("Material");

    MediaService service;
    AppEngine lrcapp;
    lrcapp.setMedia(&service);

    QQmlApplicationEngine engine;
    auto ctx = engine.rootContext();
    ctx->setContextProperty("media", &service);
    ctx->setContextProperty("app", &lrcapp);
    engine.load("./ui/CompactViewer.qml");
    engine.load("./ui/main.qml");

    return app.exec();
}
