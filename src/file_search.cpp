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

#include <tuple>

#include "file_search.h"

using namespace std;
using namespace lyrics;

pair<int, int> score(const QString &src, const QString &pattern, int score)
{
    int match = 0;
    int total = 0;
    for (const auto &v : pattern.split(QRegExp{"[ -_!@#%^&*?:]"}))
    {
        total += score;
        if (src.contains(v))
            match += score;
    }

    return make_pair(match, total);
}

double lyrics::match_score(const QString &source, const QString &artist,
                           const QString &title)
{
    int m1, m2, t1, t2;
    auto src = source.toLower();
    auto art = artist.toLower();
    auto tit = title.toLower();

    // To-do: eliminate special characters? Might affect non-latin songs though.

    tie(m1, t1) = score(src, art, 5);
    tie(m2, t2) = score(src, tit, 5);

    if (t1 + t2 == 0)
        return 1.0;
    return 0.45 * m1 / t1 + 0.6 * m2 / t2;
}
