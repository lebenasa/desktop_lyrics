/*  
 *  COPYRIGHT (c) 2015 Leben Asa. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
