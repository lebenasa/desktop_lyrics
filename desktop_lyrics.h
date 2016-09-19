#ifndef DESKTOP_LYRICS_H
#define DESKTOP_LYRICS_H

#include <QtCore>
#include <QtQuick>

#include "lyrics_parser.h"
#include "media_service.h"

class LyricsMatch : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(double score READ score WRITE setScore NOTIFY scoreChanged)
public:
    LyricsMatch(QObject *parent = nullptr);
    LyricsMatch(const QString &name, const QUrl &path,
                double score, QObject *parent = nullptr);

    QString name() const;
    void setName(QString const& val);
    QUrl path() const;
    void setPath(QUrl const& val);
    double score() const;
    void setScore(double val);

signals:
    void nameChanged(QString const&);
    void pathChanged(QUrl const&);
    void scoreChanged(int const&);

private:
    QString m_name;
    QUrl m_path;
    double m_score;
};

class AppEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MediaService* media READ media WRITE setMedia NOTIFY mediaChanged)
    Q_PROPERTY(QUrl lyricsFile READ lyricsFile WRITE setLyricsFile NOTIFY lyricsFileChanged)
    Q_PROPERTY(QString currentLine READ currentLine NOTIFY currentLineChanged)
    Q_PROPERTY(QUrl lyricsDir READ lyricsDir WRITE setLyricsDir NOTIFY lyricsDirChanged)
    Q_PROPERTY(int offset READ offset WRITE setOffset NOTIFY offsetChanged)
public:
    AppEngine(QObject *parent = nullptr);

    MediaService* media() const;
    void setMedia(MediaService *val);

    QUrl lyricsFile() const;
    void setLyricsFile(QUrl const& val);

    QString currentLine() const;

    QUrl lyricsDir() const;
    void setLyricsDir(QUrl const& val);

    int offset() const;
    void setOffset(int const& val);

public slots:
    QList<QObject*> search_lyrics(const QString &artist, const QString &title);
    void loadMainUI();
    void loadCompactUI();

signals:
    void mediaChanged(MediaService*);
    void lyricsFileChanged(QUrl const&);
    void currentLineChanged(QString const&);
    void lyricsDirChanged(QUrl const&);

    void reloadMainUI();
    void reloadCompactUI();

    void offsetChanged(int const&);

private:
    MediaService* m_media;
    QUrl m_lyricsFile;
    lyrics::lyrics_map m_lrcmap;
    lyrics::lyrics_map::iterator m_lastlrcln;
    QString m_currentLine;
    QUrl m_lyricsDir;
    QFileInfoList m_lyricsDirFiles;

    QQmlApplicationEngine m_engine;
    bool m_mainUILoaded = false;
    bool m_compactUILoaded = false;
    int m_offset;

    void update_lyrics();
    void refresh_db();

    void store_chosen(const QUrl &music, const QUrl &lyrics);
    QUrl load_chosen(const QUrl &music);

private slots:
    void setCurrentLine(int mpos);
};

#endif // DESKTOP_LYRICS_H
