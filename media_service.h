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

#ifndef MEDIA_SERVICE_H
#define MEDIA_SERVICE_H

#include <QtCore>
#include <QtDBus>

class MediaService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QVariantMap metadata READ metadata NOTIFY metadataChanged)
    Q_PROPERTY(int caps READ caps NOTIFY capsChanged)
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    // Metadata
    Q_PROPERTY(QString album READ album NOTIFY albumChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
    Q_PROPERTY(QUrl arturl READ arturl NOTIFY arturlChanged)
    Q_PROPERTY(int audioBitrate READ audioBitrate NOTIFY audioBitrateChanged)
    Q_PROPERTY(int audioSampleRate READ audioSampleRate NOTIFY audioSampleRateChanged)
    Q_PROPERTY(double bpm READ bpm NOTIFY bpmChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY commentChanged)
    Q_PROPERTY(QString genre READ genre NOTIFY genreChanged)
    Q_PROPERTY(QUrl location READ location NOTIFY locationChanged)
    Q_PROPERTY(qlonglong mtime READ mtime NOTIFY mtimeChanged)
    Q_PROPERTY(QString performer READ performer NOTIFY performerChanged)
    Q_PROPERTY(qlonglong time READ time NOTIFY timeChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(int trackNumber READ trackNumber NOTIFY trackNumberChanged)
    Q_PROPERTY(int year READ year NOTIFY yearChanged)

public:
    MediaService(QObject *parent = nullptr);

    int caps() const;

    int volume() const;
    void setVolume(int);

    QVariantMap metadata() const;

    bool isValid() const;

    int position() const;
    void setPosition(int);

    QString album() const;
    QString artist() const;
    QUrl arturl() const;
    int audioBitrate() const;
    int audioSampleRate() const;
    double bpm() const;
    QString comment() const;
    QString genre() const;
    QUrl location() const;
    qlonglong mtime() const;
    QString performer() const;
    qlonglong time() const;
    QString title() const;
    int trackNumber() const;
    int year() const;

public slots:
    void play();
    void pause();
    void stop();

    void next();
    void prev();

    void volumeDown(int);
    void volumeUp(int);
    void mute();

    void showOSD();

    void repeat(bool);

signals:
    void capsChanged(int);
    void trackChanged(QVariantMap const&);

    void volumeChanged(int);

    void metadataChanged(QVariantMap const&);

    void validChanged(bool const&);

    void positionChanged(int);

    void albumChanged(QString const&);
    void artistChanged(QString const&);
    void arturlChanged(QUrl const&);
    void audioBitrateChanged(int const&);
    void audioSampleRateChanged(int const&);
    void bpmChanged(double const&);
    void commentChanged(QString const&);
    void genreChanged(QString const&);
    void locationChanged(QUrl const&);
    void mtimeChanged(qlonglong const&);
    void performerChanged(QString const&);
    void timeChanged(qlonglong const&);
    void titleChanged(QString const&);
    void trackNumberChanged(int const&);
    void yearChanged(int const&);

private slots:
    void setCaps(int);
    void updateVolume();
    void updateMetadata();
    void updatePosition();

private:
    QDBusInterface m_player;
    int m_caps, m_volume, m_pos;
    QVariantMap m_metadata;

    template < class T, class UnaryFn >
    void asyncSet(const QString &method, const T &value, T *ptrToMember, UnaryFn fn)
    {
        auto ascb = m_player.asyncCall(method, value);
        auto watcher = new QDBusPendingCallWatcher(ascb, this);

        connect(watcher, &QDBusPendingCallWatcher::finished,
                [this, ptrToMember, fn](QDBusPendingCallWatcher *call)
        {
            QDBusPendingReply<T> reply = *call;
            if (reply.isValid())
            {
                *ptrToMember = reply.value();
                emit (this->*fn)(*ptrToMember);
            }
            else
                qWarning() << reply.error().name() << reply.error().message();
        });
    }
};

#endif // MEDIA_SERVICE_H
