#ifndef LINEARPIECE_H
#define LINEARPIECE_H

#include "splinepiece.h"
#include "point.h"

class LinearPiece
{
public:
    LinearPiece(Point *start, Point *end);
    QPointF operator ()(qreal t) const;

private:
    Point* _start;
    Point* _end;
};

#endif // LINEARPIECE_H
