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
    for (const auto &line : lyrics)
    {
        auto m = parse_line(line);
        std::move(begin(m), end(m), std::inserter(res, end(res)));
    }
    return res;
}
