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
public:
    MediaService(QObject *parent = nullptr);

    int caps() const;

    int volume() const;
    void setVolume(int);

    QVariantMap metadata() const;

    bool isValid() const;

    int position() const;
    void setPosition(int);

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
