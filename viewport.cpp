#include "viewport.h"
#include <QPainter>

Viewport::Viewport(QWidget *parent) : QWidget(parent)
{
}

void Viewport::setScene(Scene *scene)
{
    _scene = scene;
    update();
}

void Viewport::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    if (_scene)
        _scene->draw(painter);
}

