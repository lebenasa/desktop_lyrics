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
