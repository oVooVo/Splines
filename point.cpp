#include "point.h"
#include <QDebug>
#include <qmath.h>
#include <QPair>
#include "Objects/pointobject.h"
#include "preferences.h"
#include "Attributes/colorattribute.h"

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
    pen.setCosmetic(true);
    pen.setWidth(4);
    if (!_pointObject->isSelected()) {
        pen.setColor(Preferences::value<ColorAttribute>("colors.point.inactive")->color());
    } else if (isSelected()) {
        pen.setColor(Preferences::value<ColorAttribute>("colors.point.active.selected")->color());
    } else {
        pen.setColor(Preferences::value<ColorAttribute>("colors.point.active.deselected")->color());
    }
    painter.setPen(pen);
    painter.drawPoint(point());
    if (tangentsShown()) {
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

QPointF opposite(QPointF selectedOld, QPointF unselectedOld, QPointF selectedNew)
{
    if (qFuzzyIsNull(length(selectedOld)) && qFuzzyIsNull(length(unselectedOld))) {
        return selectedOld - selectedNew;
    }

    Polar selectedOldPolar = toPolar(selectedOld);
    Polar selectedNewPolar = toPolar(selectedNew);
    Polar unselectedOldPolar = toPolar(unselectedOld);

    Polar invariant;
    invariant.r   = unselectedOldPolar.r   / selectedOldPolar.r;
    invariant.phi = unselectedOldPolar.phi - selectedOldPolar.phi;

    Polar unselectedNewPolar;
    unselectedNewPolar.r   = selectedNewPolar.r   * invariant.r;
    unselectedNewPolar.phi = selectedNewPolar.phi + invariant.phi;

    return toCartesian(unselectedNewPolar);

}

void Point::moveTangent(QPointF t, TangentMode mode)
{
    switch (selectedTangent()) {
    case LeftTangent:
        if (mode == Simultan)
            _right = opposite(_left, _right, _left + t);
        _left += t;
        break;
    case RightTangent:
        if (mode == Simultan)
            _left = opposite(_right, _left, _right + t);
        _right += t;
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

void Point::setTangent(QPointF left, QPointF right)
{
    _left = left;
    _right = right;
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
