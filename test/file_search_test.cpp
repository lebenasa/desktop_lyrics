/*  
 *  COPYRIGHT (c) 2015 Leben Asa. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <catch.hpp>

#include "../src/file_search.h"
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
