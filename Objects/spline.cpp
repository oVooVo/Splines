#include "spline.h"

Spline::Spline(Object *parent) : Object(parent)
{
}

Spline::Spline(QDataStream &stream)
{
    Q_UNUSED(stream);
}

QPointF Spline::operator ()(qreal t) const
{
    t *= pieces.size();
    int index = (int) t;
    t -= index;
    return (*pieces[index])(t);
}
