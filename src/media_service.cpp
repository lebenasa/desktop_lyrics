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
const QString mpris_path = "/Player";
const QString mpris_interface = "org.freedesktop.MediaPlayer";

QString mpris_service(const QString &app)
{
    return mpris_base + "." + app;
}

/*!
 * \brief MediaService::MediaService
 * 		  Initializes MediaService object. Uses Clementine's MPRIS 2 interface.
 * \param parent
 */
MediaService::MediaService(QObject *parent)
    : QObject{ parent }, m_player{ mpris_service("amarok"), mpris_path,
                                   mpris_interface }
{
    if (isValid())
        emit validChanged(true);
    connect(&m_player, SIGNAL(CapsChange(int)), this, SLOT(setCaps(int)));
    m_player.connection().connect(mpris_service("amarok"), mpris_path, mpris_interface,
                                  "TrackChange", this, SLOT(updateMetadata()));
    m_player.connection().connect(mpris_service("amarok"), mpris_path, mpris_interface,
                                  "TrackChange", this, SIGNAL(trackChanged(QVariantMap)));
    updateVolume();
    updateMetadata();

    auto pos_updater = new QTimer(this);
    pos_updater->setTimerType(Qt::PreciseTimer);
    pos_updater->setInterval(100);
    connect(pos_updater, &QTimer::timeout, this, &MediaService::updatePosition);
    pos_updater->start();
}

int MediaService::caps() const
{
    return m_caps;
}

int MediaService::volume() const
{
    return m_volume;
}

void MediaService::setVolume(int vol)
{
    if (vol != m_volume)
        asyncSet("VolumeSet", vol, &m_volume, &MediaService::volumeChanged);
}

QVariantMap MediaService::metadata() const
{
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
    m_player.asyncCall("Prev");
}

void MediaService::volumeDown(int vol)
{
    auto ascb = m_player.asyncCall("VolumeDown", vol);
    auto watcher = new QDBusPendingCallWatcher(ascb, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, &MediaService::updateVolume);
}

void MediaService::volumeUp(int vol)
{
    auto ascb = m_player.asyncCall("VolumeUp", vol);
    auto watcher = new QDBusPendingCallWatcher(ascb, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, &MediaService::updateVolume);
}

void MediaService::mute()
{
    auto ascb = m_player.asyncCall("Mute");
    auto watcher = new QDBusPendingCallWatcher(ascb, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, &MediaService::updateVolume);
}

void MediaService::showOSD()
{
    m_player.asyncCall("ShowOSD");
}

void MediaService::repeat(bool rep)
{
    m_player.asyncCall("Repeat", rep);
}

void MediaService::setCaps(int cap)
{
    m_caps = cap;
    emit capsChanged(cap);
}

void MediaService::updateVolume()
{
    QDBusReply<int> reply = m_player.call("VolumeGet");
    if (reply.isValid())
    {
        m_volume = reply.value();
        emit volumeChanged(m_volume);
    }
    else
        qWarning() << reply.error().name() << reply.error().message();
}

void MediaService::updateMetadata()
{
    QDBusReply<QVariantMap> reply = m_player.call("GetMetadata");
    if (reply.isValid())
    {
        m_metadata = reply.value();
        emit metadataChanged(m_metadata);

        emit albumChanged(album());
        emit artistChanged(artist());
        emit arturlChanged(arturl());
        emit audioBitrateChanged(audioBitrate());
        emit audioSampleRateChanged(audioSampleRate());
        emit bpmChanged(bpm());
        emit commentChanged(comment());
        emit genreChanged(genre());
        emit locationChanged(location());
        emit mtimeChanged(mtime());
        emit performerChanged(performer());
        emit timeChanged(time());
        emit titleChanged(title());
        emit trackNumberChanged(trackNumber());
        emit yearChanged(year());
    }
    else
        qWarning() << reply.error().name() << reply.error().message();
}

int MediaService::position() const
{
    return m_pos;
}

void MediaService::setPosition(int pos)
{
    m_player.asyncCall("PositionSet", pos);
}

void MediaService::updatePosition()
{
    QDBusReply<int> reply = m_player.call("PositionGet");
    if (reply.isValid())
    {
        m_pos = reply.value();
        emit positionChanged(m_pos);
    }
    else
        qWarning() << reply.error().name() << reply.error().message();
}

QString MediaService::album() const
{
    return m_metadata.value("album").toString();
}

QString MediaService::artist() const
{
    return m_metadata.value("artist").toString();
}

QUrl MediaService::arturl() const
{
    return m_metadata.value("arturl").toUrl();
}

int MediaService::audioBitrate() const
{
    return m_metadata.value("audio-bitrate").toInt();
}

int MediaService::audioSampleRate() const
{
    return m_metadata.value("audio-samplerate").toInt();
}

double MediaService::bpm() const
{
    return m_metadata.value("bpm").toDouble();
}

QString MediaService::comment() const
{
    return m_metadata.value("comment").toString();
}

QString MediaService::genre() const
{
    return m_metadata.value("genre").toString();
}

QUrl MediaService::location() const
{
    return m_metadata.value("location").toUrl();
}

qlonglong MediaService::mtime() const
{
    return m_metadata.value("mtime").toLongLong();
}

QString MediaService::performer() const
{
    return m_metadata.value("performer").toString();
}

qlonglong MediaService::time() const
{
    return m_metadata.value("time").toLongLong();
}

QString MediaService::title() const
{
    return m_metadata.value("title").toString();
}

int MediaService::trackNumber() const
{
    return m_metadata.value("tracknumber").toInt();
}

int MediaService::year() const
{
    return m_metadata.value("year").toInt();
}

QString MediaService::timeLabel(qreal position)
{
    qlonglong ts = position * time();
    return QString::fromStdString(lyrics::time_str(std::chrono::seconds{ ts })).left(5);
}















