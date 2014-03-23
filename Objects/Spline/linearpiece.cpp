#include "linearpiece.h"

LinearPiece::LinearPiece(Point *start, Point *end)
{
    _start = start;
    _end = end;
}

QPointF LinearPiece::operator ()(double t) const
{
    return (1-t) * _start->point()+ t * _end->point();
}
