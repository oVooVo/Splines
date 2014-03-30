#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "scene.h"
#include <QWidget>
#include "manager.h"


//in the long term viewport should derive AbstractManager!
class Viewport : public QWidget, public Manager
{
public:
    Viewport(QWidget* parent = 0);
    void setScene(Scene* s);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QPointF _lastMousePos;
    QTransform _globaleTransformation;
    QPointF map(QPointF p) const;
};

#endif // VIEWPORT_H
