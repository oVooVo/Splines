#include "bezierpiece.h"

void bernstein(const qreal x, qreal &b0, qreal &b1, qreal &b2, qreal &b3)
{
    qreal x2 = x*x;
    qreal x3 = x2*x;

    b0 = 1 - 3*x + 3*x2 - x3;
    b1 = 3*x - 6*x2 + 3*x3;
    b2 = 3*x2 - 3*x3;
    b3 = x3;
}

BezierPiece::BezierPiece(Point *start, Point *end)
{
    _start = start;
    _end = end;
}

QPointF BezierPiece::operator ()(qreal t) const
{
    qreal b0, b1, b2, b3;
    bernstein(t, b0, b1, b2, b3);
    return b0 * _start->point()
         + b1 * _start->rightTangentGlobal()
         + b2 * _end->leftTangentGlobal()
         + b3 * _end->point();
}
