#ifndef LYRICS_PARSER_H
#define LYRICS_PARSER_H

#include <algorithm>
#include <map>
#include <string>

#include <QtCore>

namespace lyrics
{
using lyrics_map = std::map<int, QString>;

lyrics_map parse_line(const QString &line);
int to_ms(const QString &time);
lyrics_map parse_all(const QStringList &lyrics);
}

#endif // LYRICS_PARSER_H
