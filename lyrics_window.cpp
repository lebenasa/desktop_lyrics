#include <QtCore>

#include "lyrics_window.h"

LyricsWindow::LyricsWindow(QWindow *parent)
    : QQuickWindow{ parent }, m_pressed{ false }
{
    setFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
}

void LyricsWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        last_x = ev->globalX();
        last_y = ev->globalY();
        m_pressed = true;
        ev->accept();
        return;
    }
    QQuickWindow::mousePressEvent(ev);
}

void LyricsWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_pressed)
    {
        auto diff_x = ev->globalX() - last_x;
        auto diff_y = ev->globalY() - last_y;
        setPosition(x() + diff_x, y() + diff_y);
        last_x = ev->globalX();
        last_y = ev->globalY();
        ev->accept();
        return;
    }
    QQuickWindow::mouseMoveEvent(ev);
}

void LyricsWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    m_pressed = false;
    ev->accept();
}
