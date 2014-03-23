#include "bezierpiece.h"

BezierPiece::BezierPiece(Point *start, Point *end)
{
    _start = start;
    _end = end;
}

QPointF BezierPiece::operator ()(double t) const
{
    qreal b0, b1, b2, b3;
    bernstein(t, b0, b1, b2, b3);
    return b0 * _start->point()
         + b1 * _start->rightTangent()
         + b2 * _end->leftTangent()
         + b3 * _end->point();
}
