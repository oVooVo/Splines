#include "pointobject.h"
#include <QDebug>
#include <limits>

const qreal PointObject::EPS = 4.0;

PointObject::PointObject(Object* parent)  : Object(parent)
{

}

void PointObject::deserialize(QDataStream &stream)
{
    Object::deserialize(stream);
    stream >> _points;
    for (Point* p : _points)
        if (p->isSelected()) _selected.append(p);
}

PointObject::~PointObject()
{
    qDeleteAll(_points);
}

void PointObject::serialize(QDataStream &stream) const
{
    Object::serialize(stream);
    stream << _points;
}

void PointObject::addPoint(Point* p)
{
    _points.append(p);
    emit changed();
}

void PointObject::selectAllPoints()
{
    if (_selected.size() == _points.size()) return;
    blockSignals(true);
    for (Point* p : points()) {
        selectPoint(p);
    }
    blockSignals(false);
    emit changed();
}

void PointObject::deselectAllPoints()
{
    if (_selected.isEmpty()) return;
    blockSignals(true);
    for (Point* p : points()) {
        deselectPoint(p);
    }
    blockSignals(false);
    emit changed();
}

void PointObject::selectPoint(Point* p)
{
    if (p->isSelected()) return;
    p->select();
    _selected.append(p);
    emit changed();
}

void PointObject::deselectPoint(Point* p)
{
    if (!p->isSelected()) return;
    p->deselect();
    _selected.removeOne(p);
    emit changed();
}

void PointObject::toggleSelectionOfPoint(Point *p)
{
    if (p->isSelected())
        selectPoint(p);
    else
        deselectPoint(p);
    emit changed();
}

Point* PointObject::pointAt(QPointF pos) const
{
    qreal dist = EPS;
    Point* point = 0;
    for (Point* p : points()) {
        qreal d = (p->point() - pos).manhattanLength();
        if (d < dist) {
            point = p;
            dist = d;
        }
    }
    return point;
}


Point* PointObject::selectTangentAt(const QPointF pos) const
{
    auto distanceOfTangent = [](Point* p, Point::Tangent t, QPointF pos) {
        return (pos - p->tangent(t)).manhattanLength();
    };

    Point::Tangent tangent = Point::NoTangent;

    qreal dist = EPS;
    Point* pointWithTangent = 0;
    for (Point* p : points()) {
        qreal d1 = distanceOfTangent(p, Point::LeftTangent, pos);
        qreal d2 = distanceOfTangent(p, Point::RightTangent, pos);
        if (d1 < d2 && d1 < dist) {
            dist = d1;
            tangent = Point::LeftTangent;
            pointWithTangent = p;
        } else if (d2 < dist) {
            dist = d2;
            tangent = Point::RightTangent;
            pointWithTangent = p;
        }
    }

    if (pointWithTangent)
        pointWithTangent->selectTangent(tangent);

    return pointWithTangent;
}











