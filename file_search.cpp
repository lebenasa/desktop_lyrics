#include <tuple>

#include "file_search.h"

using namespace std;
using namespace lyrics;

pair<int, int> score(const QString &src, const QString &pattern, int score)
{
    int match = 0;
    int total = 0;
    for (const auto &v : pattern.split(" "))
    {
        total += score;
        if (src.contains(v))
            match += score;
    }

    if (match == total)
        match += 2 * score;
    total += 2 * score;

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
    return 0.5 * m1 / t1 + 0.5 * m2 / t2;
}
