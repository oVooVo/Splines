#include "viewport.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

Viewport::Viewport(QWidget *parent) : QWidget(parent)
{
}

void Viewport::setScene(Scene *scene)
{
    if (_scene == scene) return;

    if (_scene)
        disconnect(_scene, 0, this, 0);

    _scene = scene;

    if (_scene) {
        connect(_scene, SIGNAL(changed()), this, SLOT(update()));
    }

    update();
}

void Viewport::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    _globaleTransformation = QTransform::fromTranslate(width()/2, height()/2);
    painter.setTransform(_globaleTransformation);
    if (_scene)
        _scene->draw(painter);
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    _lastMousePos = pos;
    if (_scene) {
        switch (event->button()) {
        case Qt::LeftButton :
            if (insertMode) _scene->insert(pos);
            else _scene->select(pos, event->modifiers() == Qt::CTRL);
            break;
        case Qt::RightButton:
            _scene->remove(pos);
            break;
        case Qt::MiddleButton:
        default:
            break;
        }
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    QPointF t = pos - _lastMousePos;

    if (_scene) {
        _scene->moveSelected(t);
    }
    _lastMousePos = map(event->pos());
}

QPointF Viewport::map(QPointF p) const
{
    return _globaleTransformation.inverted().map(p);
}







