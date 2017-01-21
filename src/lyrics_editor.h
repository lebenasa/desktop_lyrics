#ifndef LYRICS_EDITOR_H
#define LYRICS_EDITOR_H

#include <QObject>

class LyricsLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(QString lyrics READ lyrics WRITE setLyrics NOTIFY lyricsChanged)
public:
    LyricsLine(QObject *parent = nullptr);

    QString timestamp() const;
    void setTimestamp(const QString& timestamp);
    QString lyrics() const;
    void setLyrics(const QString& lyrics);

signals:
    void timestampChanged(const QString& timestamp);
    void lyricsChanged(const QString& lyrics);

private:
    QString m_timestamp;
    QString m_lyrics;
};

#endif // LYRICS_EDITOR_H
