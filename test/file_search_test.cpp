#include <catch.hpp>

#include "file_search.h"
using namespace std;
using namespace lyrics;

TEST_CASE("Match scoring algorithm", "[single-file]")
{
    REQUIRE(match_score("", "", "") == 1.0);
    REQUIRE(match_score("Aoi Tada - Brave Song.lrc", "Aoi Tada", "Brave Song") == 1.0);
    REQUIRE(match_score("Aoi Tada - Yake Ochinai Tsubasa.lrc", "Aoi Tada", "Brave Song") >= 0.5 );
    REQUIRE(match_score("Haruna Luna - Brave Song.lrc", "Aoi Tada", "Brave Song") >= 0.5);
    REQUIRE(match_score("Haruna Luna - Yake Ochinai Tsubasa.lrc", "Aoi Tada", "Brave Song") == 0.0);
    REQUIRE(match_score("(K)nowName - Harvest.lrc", "(k)nowname", "Harvest") == 1.0);
}
