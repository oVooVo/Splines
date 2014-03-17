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
    if (_scene)
        _scene->draw(painter);
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    _lastMousePos = event->pos();
    if (_scene) {
        switch (event->button()) {
        case Qt::LeftButton :
            if (insertMode) _scene->insert(event->pos());
            else _scene->select(event->pos(), event->modifiers() == Qt::CTRL);
            break;
        case Qt::RightButton:
            _scene->remove(event->pos());
            break;
        case Qt::MiddleButton:
        default:
            break;
        }
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    QPointF t = event->pos() - _lastMousePos;
    if (_scene) {
        qDebug() << "moveSelected()";
        _scene->moveSelected(t);
    }
    _lastMousePos = event->pos();
}

