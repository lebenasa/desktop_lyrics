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

#include <chrono>

#include "media_service.h"
#include "lyrics_parser.h"

/*!
  \class MediaService
  \brief Base implementation for connection with media service provider.
         Uses Clementine DBus as default.
 */

const QString mpris_base = "org.mpris.MediaPlayer2";
const QString mpris_path = "/org/mpris/MediaPlayer2";
const QString mpris_base_interface = "org.mpris.MediaPlayer2";

QString mpris_service(const QString &app)
{
    return mpris_base + "." + app;
}

QString mpris_interface(const QString &interface) {
    if (interface.isEmpty())
        return mpris_base_interface;
    return mpris_base_interface + "." + interface;
}

/*!
 * \brief MediaService::MediaService
 * 		  Initializes MediaService object. Uses Clementine's MPRIS 2 interface.
 * \param parent
 */
MediaService::MediaService(QObject *parent)
    : QObject{ parent },
      m_player{ mpris_service("clementine"), mpris_path,
                mpris_interface("Player") }
{
    if (isValid()) {
        emit validChanged(true);
    }
    else {
        qDebug() << "Failed to initialize Media Service";
        return;
    }
    QDBusConnection::sessionBus().connect(mpris_service("clementine"), mpris_path, "org.freedesktop.DBus.Properties",
                                          "PropertiesChanged", this, SLOT(playerPropertyChanged()));
    playerPropertyChanged();
    auto pos_updater = new QTimer(this);
    pos_updater->setTimerType(Qt::PreciseTimer);
    pos_updater->setInterval(50);
    connect(pos_updater, &QTimer::timeout, this, &MediaService::updatePosition);
    pos_updater->start();
}

void MediaService::playerPropertyChanged() {
    emit volumeChanged(volume());

    emit metadataChanged(metadata());

    emit albumChanged(album());
    emit artistChanged(artist());
    emit arturlChanged(arturl());
    emit audioBitrateChanged(audioBitrate());
    emit audioSampleRateChanged(audioSampleRate());
    emit bpmChanged(bpm());
    emit commentChanged(comment());
    emit genreChanged(genre());
    emit locationChanged(location());
    emit performerChanged(performer());
    emit lengthChanged(length());
    emit titleChanged(title());
    emit trackNumberChanged(trackNumber());
    emit trackIDChanged(trackID());
    emit yearChanged(year());
}

float MediaService::volume() const
{
    return m_player.property("Volume").toFloat();
}

void MediaService::setVolume(float vol)
{
    m_player.setProperty("Volume", vol);
}

const QVariantMap &MediaService::metadata()
{
    m_metadata = m_player.property("Metadata").toMap();
    return m_metadata;
}

bool MediaService::isValid() const
{
    return m_player.isValid();
}

void MediaService::play()
{
    m_player.asyncCall("Play");
}

void MediaService::pause()
{
    m_player.asyncCall("Pause");
}

void MediaService::stop()
{
    m_player.asyncCall("Stop");
}

void MediaService::next()
{
    m_player.asyncCall("Next");
}

void MediaService::prev()
{
    m_player.asyncCall("Previous");
}

void MediaService::volumeDown(float vol)
{
    setVolume(volume() - vol);
}

void MediaService::volumeUp(float vol)
{
    setVolume(volume() + vol);
}

void MediaService::mute()
{
    setVolume(0.0);
}

void MediaService::showOSD()
{
    m_player.asyncCall("ShowOSD");
}

void MediaService::repeat(bool rep)
{
    m_player.asyncCall("Repeat", rep);
}

int MediaService::position() const
{
    return m_player.property("Position").toInt();
}

void MediaService::setPosition(int pos)
{
    QDBusObjectPath trackPath{ trackID() };
    m_player.asyncCall("SetPosition", QVariant::fromValue(trackPath), pos);
}

void MediaService::updatePosition()
{
    emit positionChanged(position());
}

QString MediaService::album() const
{
    return m_metadata.value("xesam:album").toString();
}

QString MediaService::artist() const
{
    return m_metadata.value("xesam:artist").toString();
}

QUrl MediaService::arturl() const
{
    return m_metadata.value("mpris:artUrl").toUrl();
}

int MediaService::audioBitrate() const
{
    return m_metadata.value("bitrate").toInt();
}

int MediaService::audioSampleRate() const
{
    return m_metadata.value("samplerate").toInt();
}

double MediaService::bpm() const
{
    return m_metadata.value("bpm").toDouble();
}

QString MediaService::comment() const
{
    return m_metadata.value("xesam:comment").toString();
}

QString MediaService::genre() const
{
    return m_metadata.value("xesam:genre").toString();
}

QUrl MediaService::location() const
{
    return m_metadata.value("xesam:url").toUrl();
}

QString MediaService::performer() const
{
    return m_metadata.value("xesam:artist").toString();
}

qlonglong MediaService::length() const
{
    return m_metadata.value("mpris:length").toLongLong();
}

QString MediaService::title() const
{
    return m_metadata.value("xesam:title").toString();
}

int MediaService::trackNumber() const
{
    return m_metadata.value("xesam:tracknumber").toInt();
}

QString MediaService::trackID() const
{
    return m_metadata.value("mpris:trackid").toString();
}

int MediaService::year() const
{
    return m_metadata.value("year").toInt();
}

QString MediaService::timeLabel(qreal position)
{
    qlonglong ts = position * length();
    return QString::fromStdString(lyrics::time_str(std::chrono::microseconds{ ts })).left(5);
}
