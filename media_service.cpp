#include "media_service.h"

MediaService::MediaService(QObject *parent)
    : QObject{ parent }, m_player{ "org.mpris.clementine", "/Player",
                                   "org.freedesktop.MediaPlayer" }
{
    if (isValid())
        emit validChanged(true);
    connect(&m_player, SIGNAL(CapsChange(int)), this, SLOT(setCaps(int)));
    m_player.connection().connect("org.mpris.clementine", "/Player", "org.freedesktop.MediaPlayer",
                                  "TrackChange", this, SLOT(updateMetadata()));
    m_player.connection().connect("org.mpris.clementine", "/Player", "org.freedesktop.MediaPlayer",
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
