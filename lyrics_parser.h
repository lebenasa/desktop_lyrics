#ifndef LYRICS_PARSER_H
#define LYRICS_PARSER_H

#include <algorithm>
#include <map>
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <QtCore>

namespace lyrics
{
using lyrics_map = std::map<int, QString>;

lyrics_map parse_line(const QString &line);
lyrics_map parse_all(const QStringList &lyrics);

int to_ms(const QString &time);
template< class T, class Rep >
inline std::string time_str(const std::chrono::duration<T, Rep> &time)
{
    int m = std::chrono::duration_cast<std::chrono::minutes>(time).count();
    int s = std::chrono::duration_cast<std::chrono::seconds>(time).count();
    int z = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
    std::ostringstream res;
    res << std::setfill('0') << std::setw(2) << m;
    res << ":" << std::setfill('0') << std::setw(2) << s - m * 60;
    res << "." << std::setfill('0') << std::setw(2) << (z - s * 1000) / 10;
    return res.str();
}

}

#endif // LYRICS_PARSER_H
