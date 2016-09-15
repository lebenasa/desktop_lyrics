#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <QtCore>

namespace lyrics
{

double match_score(const QString &source, const QString &artist, const QString &title);

}

#endif // FILE_SEARCH_H
