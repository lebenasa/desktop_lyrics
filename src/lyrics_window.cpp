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
    }
    else if (ev->button() == Qt::RightButton)
        emit openContextMenu(ev->pos());
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
    }
    QQuickWindow::mouseMoveEvent(ev);
}

void LyricsWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    m_pressed = false;
    ev->accept();
}
