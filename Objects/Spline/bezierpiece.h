#ifndef BEZIERPIECE_H
#define BEZIERPIECE_H

#include "Objects/Spline/splinepiece.h"

class BezierPiece : public SplinePiece
{
public:
    BezierPiece(Point* start, Point* end);
    QPointF operator ()(double t) const;

private:
    Point* _start;
    Point* _end;
};

#endif // BEZIERPIECE_H
