#include <algorithm>

#include "desktop_lyrics.h"
using namespace std;

AppEngine::AppEngine(QQuickItem *parent)
    : QQuickItem{ parent }, m_media{ nullptr }, m_lastlrcln{ begin(m_lrcmap) }
{
}

MediaService* AppEngine::media() const
{
    return m_media;
}

void AppEngine::setMedia(MediaService *val)
{
    if (val != m_media)
    {
        m_media = val;
        connect(val, &MediaService::positionChanged, this, &AppEngine::setCurrentLine);
        emit mediaChanged(val);
    }
}

QUrl AppEngine::lyricsFile() const
{
    return m_lyricsFile;
}

void AppEngine::setLyricsFile(const QUrl& val)
{
    if (val != m_lyricsFile)
    {
        m_lyricsFile = val;
        emit lyricsFileChanged(val);
        update_lyrics();
    }
}

void AppEngine::update_lyrics()
{
    QFile lf{ lyricsFile().toLocalFile() };
    if (lf.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream lt{ &lf };
        auto ls = lt.readAll().split("\n");
        m_lrcmap = lyrics::parse_all(ls);
        m_lastlrcln = begin(m_lrcmap);
    }
    else
    {
        qWarning() << "Failed to open" << lyricsFile();
    }
}

QString AppEngine::currentLine() const
{
    return m_currentLine;
}

void AppEngine::setCurrentLine(int mpos)
{
    auto pred = [mpos](pair<int, QString> const &v) { return v.first > mpos; };
    auto it = find_if(m_lastlrcln, end(m_lrcmap), pred);
    if (it != end (m_lrcmap) && it->first - mpos > 1000)
        it = end(m_lrcmap);
    if (it == end(m_lrcmap))
    {
        it = find_if(begin(m_lrcmap), end(m_lrcmap), pred);
        if (it == end(m_lrcmap))
            return;
    }
    if (it != begin(m_lrcmap))
        --it;
    if (it->second != m_currentLine)
    {
        m_currentLine = it->second;
        emit currentLineChanged(m_currentLine);
        m_lastlrcln = it;
    }
}
