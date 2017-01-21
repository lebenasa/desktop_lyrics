#include <catch.hpp>

#include "../src/lyrics_parser.h"
using namespace lyrics;

SCENARIO("Converting lyrics map to model", "[lyrics_model]")
{
    GIVEN("Empty lyrics map from file")
    {
        lyrics_map lm;
        WHEN("Converted to lyrics model")
        {
            auto lv = lyrics_model(lm);
            THEN("The lyrics model is also empty")
            {
                REQUIRE(lv.size() == 0);
                REQUIRE(lv.empty() == true);
            }
        }
    }

    GIVEN("Valid lyrics map")
    {
        lyrics_map lm;
        lm[0] = "Line 1";
        lm[1] = "Line 2";
        lm[2] = "Line 3";
        lm[3] = "Line 4";
        WHEN("Converted to lyrics model")
        {
            auto lv = lyrics_model(lm);
            THEN("The lyrics model has the same size as the lyrics map")
            {
                REQUIRE(lv.size() == lm.size());
            }
        }
    }

    GIVEN("Lyrics map with lines without timestamp")
    {
        WHEN("Converted to lyrics model")
        {
            auto lv = lyrics_model(lm);
            THEN("The lyrics model has the same size as the lyrics map")
            {
                REQUIRE(lv.size() == lm.size());
            }
        }
    }
}
