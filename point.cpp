#include "point.h"
#include <QDebug>

Point::Point(QPointF point)
{
    qDebug() << point;
    _point = point;

    qDebug() << "blubblub " << _point;
}

void Point::setPoint(QPointF p)
{
    qDebug() << "set point" << p;
    _point = p;
}

void Point::draw(QPainter &painter)
{
    qDebug() << "draw point" << point();
    painter.save();
    QPen pen;
    pen.setColor(_select ? QColor(100, 255, 0) : QColor(0, 0, 0));
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawPoint(point());
    if (_showTangents && _select) {
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawPoint(point() + leftTangent());
        painter.drawPoint(point() + rightTangent());
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(point() + leftTangent(), point());
        painter.drawLine(point() + rightTangent(), point());
    }
    painter.restore();
}
