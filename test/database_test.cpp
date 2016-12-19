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

#include <QtCore>
#include <QtSql>

TEST_CASE("Using QSqlTableModel to store data", "")
{
    QSqlTableModel model;
    model.setTable("lyrics_test");
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    qDebug() << model.select();
    model.setHeaderData(0, Qt::Horizontal, "Music Path");
    model.setHeaderData(1, Qt::Horizontal, "Lyrics Path");
    model.setHeaderData(2, Qt::Horizontal, "Lyrics Name");

    QSqlRecord rec_a;
    rec_a.setValue(0, "/path/to/music.mp3");
    rec_a.setValue("lyricspath", "path/to/lyrics.lrc");
    rec_a.setValue(2, "lyrics.lrc");
    if (model.insertRecord(-1, rec_a))
        qDebug() << "Insert success";
    else
        return;
    model.submitAll();
    qDebug() << model.select();
    qDebug() << model.record(0).value("musicpath").toString();
    qDebug() << model.record(0).value(1).toString();
    qDebug() << model.record(0).value(2).toString();
}
