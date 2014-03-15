#include "spline.h"

Spline::Spline(Object *parent) : Object(parent)
{
}

QPointF Spline::operator ()(qreal t) const
{
    t *= pieces.size();
    int index = (int) t;
    t -= index;
    return (*pieces[index])(t);
}
