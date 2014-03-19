#include "viewport.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include "interaction.h"

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

    Interaction interaction(event->button(), pos, Interaction::SingleClick, event->modifiers());
    _scene->processInteraction(interaction);
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    QPointF t = pos - _lastMousePos;
    Interaction interaction(t, event->modifiers());
    _scene->processInteraction(interaction);
    _lastMousePos = map(event->pos());
}

void Viewport::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    _lastMousePos = pos;

    Interaction interaction(event->button(), pos, Interaction::DoubleClick, event->modifiers());
    _scene->processInteraction(interaction);
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    _lastMousePos = pos;

    Interaction interaction(event->button(), pos, Interaction::DoubleClick, event->modifiers());
    _scene->processInteraction(interaction);
}

QPointF Viewport::map(QPointF p) const
{
    return _globaleTransformation.inverted().map(p);
}







