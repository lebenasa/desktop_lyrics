#include <catch.hpp>
#include "../lyrics_parser.h"

TEST_CASE("Parsing a line of LRC file", "[line]")
{
    REQUIRE(lyrics::to_ms("01:05.04") == 60000 + 5 * 1000 + 40);
    auto lrc = lyrics::parse_line("[01:05.09][02:18.60]Kakkoyoku nai yasashi sa ga soba ni aru kara");
    REQUIRE(lrc[lyrics::to_ms("01:05.09")] == "Kakkoyoku nai yasashi sa ga soba ni aru kara");
    REQUIRE(lrc[lyrics::to_ms("02:18.60")] == "Kakkoyoku nai yasashi sa ga soba ni aru kara");
}

TEST_CASE("Parsing a whole lyrics", "[!hide][lyrics]")
{
    QFile lrc{"YUI - Good-bye Days.lrc" };
    QStringList lrcs;
    if (lrc.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream out(&lrc);
        lrcs = out.readAll().split('\n');
    }
    auto lmap = lyrics::parse_all(lrcs);
    for (auto i = begin(lmap); i != end(lmap); ++i)
    {
//        qDebug() << i->first << i->second;
    }
}
