#ifndef DESKTOP_LYRICS_H
#define DESKTOP_LYRICS_H

#include <QtCore>
#include <QtQuick>

#include "lyrics_parser.h"
#include "media_service.h"

class AppEngine : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(MediaService* media READ media WRITE setMedia NOTIFY mediaChanged)
    Q_PROPERTY(QUrl lyricsFile READ lyricsFile WRITE setLyricsFile NOTIFY lyricsFileChanged)
    Q_PROPERTY(QString currentLine READ currentLine NOTIFY currentLineChanged)
public:
    AppEngine(QQuickItem *parent = nullptr);

    MediaService* media() const;
    void setMedia(MediaService *val);

    QUrl lyricsFile() const;
    void setLyricsFile(QUrl const& val);

    QString currentLine() const;

signals:
    void mediaChanged(MediaService*);
    void lyricsFileChanged(QUrl const&);
    void currentLineChanged(QString const&);

private:
    MediaService* m_media;
    QUrl m_lyricsFile;
    lyrics::lyrics_map m_lrcmap;
    lyrics::lyrics_map::iterator m_lastlrcln;
    QString m_currentLine;

    void update_lyrics();

private slots:
    void setCurrentLine(int mpos);
};

#endif // DESKTOP_LYRICS_H
