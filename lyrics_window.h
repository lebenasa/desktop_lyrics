#ifndef LYRICS_WINDOW_H
#define LYRICS_WINDOW_H

#include "QQuickWindow"

class LyricsWindow : public QQuickWindow
{
    Q_OBJECT
    int last_x, last_y;
    bool m_pressed;
public:
    LyricsWindow(QWindow *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // LYRICS_WINDOW_H
