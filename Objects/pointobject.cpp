#include "pointobject.h"

const qreal PointObject::EPS = 4.0;

PointObject::PointObject(Object* parent)  : Object(parent)
{

}

PointObject::PointObject(QDataStream& stream) : Object(stream)
{
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


/*
void PointObject::handleSelection(Point *p, bool extended)
{
    if (!p->isSelected()) {
        if (!extended) {
            deselectAll();
        }
        select(p);
    } else {
        if (extended) {
            deselect(p);
        } else {
            deselectAll();
            select(p);
        }
    }
}
*/
