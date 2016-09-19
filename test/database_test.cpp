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
