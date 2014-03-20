#include "point.h"
#include <QDebug>

Point::Point(QPointF point)
{
    _point = point;
}

void Point::setPoint(QPointF p)
{
    _point = p;
}

void Point::draw(QPainter &painter)
{
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

void Point::move(QPointF t)
{
    _point += t;
}

QDataStream& operator<<(QDataStream& out, const Point* s)
{
    out << s->_point << s->_left << s->_right << (quint8) s->_select << (quint8) s->_showTangents;
    return out;
}

QDataStream& operator>>(QDataStream& in, Point* &s)
{
    s = new Point(QPointF());

    quint8 st, sel;

    in >> s->_point >> s->_left >> s->_right >> sel >> st;
    s->_select = (bool) sel;
    s->_showTangents = (bool) st;

    return in;
}
