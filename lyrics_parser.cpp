#include "lyrics_parser.h"
using namespace lyrics;

lyrics_map lyrics::parse_line(const QString &line)
{
    using namespace std;
    lyrics_map res;
    QRegularExpression re{ R"reg(\[(\d\d:\d\d\.\d\d)\])reg" };
    auto i = re.globalMatch(line);
    QRegularExpressionMatch match;

    while (i.hasNext())
    {
        match = i.next();
        res[to_ms(match.captured(1))] = "";
    }

    auto lyric = line.mid(match.capturedEnd(1) + 1);
    lyric.remove(QRegularExpression{R"reg(<\d\d:\d\d.\d\d>)reg"});
    for (auto i = begin(res); i != end(res); ++i)
        i->second = lyric;

    return res;
}

int lyrics::to_ms(const QString &time)
{
    auto tt = QTime::fromString(time, "mm:ss.z");
    return tt.minute() * 60000 + tt.second() * 1000 + tt.msec();
}

lyrics_map lyrics::parse_all(const QStringList &lyrics)
{
    lyrics_map res;
    auto i = lyrics.begin();
    for (; parse_line(*i).empty(); ++i)
    {
        if (i->contains("[offset:"))
        {
            QRegularExpression re{ R"reg(\d+)reg" };
            auto match = re.match(*i);
            if (match.hasMatch())
                res[-1] = match.captured(0);
        }
    }
    for (--i; i != lyrics.end(); ++i)
    {
        auto m = parse_line(*i);
        std::move(begin(m), end(m), std::inserter(res, end(res)));
    }
    return res;
}
