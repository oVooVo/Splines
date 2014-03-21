#include "point.h"
#include <QDebug>
#include <qmath.h>
#include <QPair>

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
    pen.setColor(isSelected() ? QColor(100, 255, 0) : QColor(0, 0, 0));
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawPoint(point());
    if (true) {
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawPoint(leftTangent());
        painter.drawPoint(rightTangent());
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(leftTangent(), point());
        painter.drawLine(rightTangent(), point());
    }
    painter.restore();
}

void Point::move(QPointF t)
{
    _point += t;
}

qreal length(QPointF p)
{
    return qSqrt(QPointF::dotProduct(p, p));
}

Polar toPolar(QPointF p)
{
    Polar polar;
    polar.r = length(p);
    polar.phi = qAtan2(p.y(), p.x());
    return polar;
}

QPointF toCartesian(Polar p)
{
    return QPointF(
                qCos(p.phi) * p.r,
                qSin(p.phi) * p.r);
}

void Point::moveTangent(QPointF t, TangentMode mode)
{
    qreal r = 1;
    qreal phi = 0;
    if (mode == Simultan) {
        QPointF selectedOld = tangent(selectedTangent()) - _point;
        r = length(selectedOld + t) / length(selectedOld);
        phi = toPolar(selectedOld + t).phi - toPolar(selectedOld).phi;
    }
    Polar polar;
    switch (selectedTangent()) {
    case LeftTangent:
        _left += t;
        if (mode == Simultan) {
            polar = toPolar(_right);
            polar.phi += phi;
            _right = toCartesian(polar);
            _right *= r;
        }
        break;
    case RightTangent:
        _right += t;
        if (mode == Simultan) {
            polar = toPolar(_left);
            polar.phi += phi;
            _left = toCartesian(polar);
            _left *= r;
        }
        break;
    case NoTangent:
    default:
        break;
    }
}

void Point::selectTangent(Tangent tangent)
{
    _selectedTangent = tangent;
}

QDataStream& operator<<(QDataStream& out, const Point* s)
{
    out << s->_point << s->_left << s->_right << (quint8) s->_isSelected << (quint8) s->_showTangents;
    return out;
}

QDataStream& operator>>(QDataStream& in, Point* &s)
{
    s = new Point(QPointF());

    quint8 st, sel;

    in >> s->_point >> s->_left >> s->_right >> sel >> st;
    s->_isSelected = (bool) sel;
    s->_showTangents = (bool) st;

    return in;
}
