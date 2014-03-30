#include "viewport.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include "interaction.h"
#include "preferences.h"
#include "Attributes/colorattribute.h"

Viewport::Viewport(QWidget *parent) : QWidget(parent)
{
}

void Viewport::setScene(Scene *s)
{
    Manager::setScene(s);

    if (scene()) {
        connect(scene(), SIGNAL(changed()), this, SLOT(update()));
    }

    update();
}

void Viewport::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (scene()) {
        painter.fillRect(rect(), Preferences::value<ColorAttribute>("colors.background")->color());
        _globaleTransformation = QTransform::fromTranslate(width()/2, height()/2);
        painter.setTransform(_globaleTransformation);
        scene()->draw(painter);
    } else {
        painter.fillRect(rect(), Qt::gray);
    }
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    _lastMousePos = pos;

    Interaction interaction(event->button(), pos, Interaction::Press, Interaction::SingleClick, event->modifiers());
    if (scene()) scene()->processInteraction(interaction);
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    QPointF t = pos - _lastMousePos;
    Interaction interaction(t, event->modifiers());
    if (scene()) scene()->processInteraction(interaction);
    _lastMousePos = map(event->pos());
}

void Viewport::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    _lastMousePos = pos;

    Interaction interaction(event->button(), pos, Interaction::Press, Interaction::DoubleClick, event->modifiers());
    if (scene()) scene()->processInteraction(interaction);
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF pos = map(event->pos());
    _lastMousePos = pos;

    Interaction interaction(event->button(), pos, Interaction::Release, Interaction::NoClick, event->modifiers());
    if (scene()) scene()->processInteraction(interaction);
}

QPointF Viewport::map(QPointF p) const
{
    return _globaleTransformation.inverted().map(p);
}







