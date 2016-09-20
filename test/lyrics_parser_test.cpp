#include <chrono>

#include <catch.hpp>
#include "../lyrics_parser.h"

TEST_CASE("Parsing a line of LRC file", "[line]")
{
    SECTION("Regular lyrics")
    {
        REQUIRE(lyrics::to_ms("01:05.04") == 60000 + 5 * 1000 + 40);
        auto lrc = lyrics::parse_line("[01:05.09][02:18.60]Kakkoyoku nai yasashi sa ga soba ni aru kara");
        REQUIRE(lrc[lyrics::to_ms("01:05.09")] == "Kakkoyoku nai yasashi sa ga soba ni aru kara");
        REQUIRE(lrc[lyrics::to_ms("02:18.60")] == "Kakkoyoku nai yasashi sa ga soba ni aru kara");
    }
    SECTION("Lyrics with karaoke tags")
    {
        auto lrc = lyrics::parse_line("[00:16.49]fu<00:16.80>n<00:17.10> <00:17.24>wari yure<00:18.00>ru<00:18.84> <00:19.12>KAPUCHII<00:20.00>NO<00:20.77>");
        REQUIRE(lrc[lyrics::to_ms("00:16.49")] == "fun wari yureru KAPUCHIINO");
    }
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
        qDebug() << i->first << i->second;
    }
}

TEST_CASE("Formatting timestamp", "[editor]")
{
    namespace chr = std::chrono;
    REQUIRE(lyrics::time_str(chr::seconds{ 0 }) == "00:00.00");
    REQUIRE(lyrics::time_str(chr::seconds{ 246 }) == "04:06.00");
    REQUIRE(lyrics::time_str(chr::milliseconds{ 246120 }) == "04:06.12");
}
