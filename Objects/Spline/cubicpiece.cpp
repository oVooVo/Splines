#include "cubicpiece.h"
#include <qmath.h>

CubicPiece::CubicPiece(Point *a, Point *b, Point *c, Point *d)
{
    _a = a;
    _b = b;
    _c = c;
    _d = d;
}

QPointF CubicPiece::operator ()(double t) const
{
    QPointF r;
    r += cube(1-t)/6.0 * _a->point();
    r += (3*cube(t)-6*sqr(t)+4)/6.0*_b->point();
    r += (-3*cube(t)+3*sqr(t)+3*t+1)/6.0*_c->point();
    r += cube(t)/6.0 * _d->point();
    return r;
}


