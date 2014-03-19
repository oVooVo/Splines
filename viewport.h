#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "scene.h"
#include <QWidget>

class Viewport : public QWidget
{
public:
    Viewport(QWidget* parent = 0);
    void setScene(Scene* scene);
    Scene* scene() const { return _scene; }
    bool insertMode;


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Scene* _scene = 0;
    QPointF _lastMousePos;
    QTransform _globaleTransformation;
    QPointF map(QPointF p) const;
};

#endif // VIEWPORT_H
