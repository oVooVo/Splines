#include "bpiece.h"
#include <qmath.h>
#include <QDebug>

BPiece::BPiece(Point *a, Point *b, Point *c, Point *d, Type type)
{
    _a = a;
    _b = b;
    _c = c;
    _d = d;
    _type = type;
}



QPointF BPiece::operator ()(double t) const
{
    QPointF r;
    switch (_type) {
    case Middle:
        r += (   cube(1 - t)                 )/6.0 * _a->point();
        r += ( 3*cube(t) - 6*sqr(t)       + 4)/6.0 * _b->point();
        r += (-3*cube(t) + 3*sqr(t) + 3*t + 1)/6.0 * _c->point();
        r += (   cube(t)                     )/6.0 * _d->point();
        break;
    case End:
        r += (   cube(1 - t)                 )/6.0 * _a->point();
        r += ( 2*cube(t) - 6*sqr(t)       + 4)/6.0 * _b->point();
        r += (-7*cube(t) + 3*sqr(t) + 3*t + 1)/6.0 * _c->point();
        r += (   cube(t)                     )/1.0 * _d->point();
        break;
    case Start:
        r += (   cube(1 - t)                 )/1.0 * _a->point();
        r += (12*t-18*sqr(t)+7*cube(t))/6.0 * _b->point();
        r += (6*t-2*cube(t))/6.0 * _c->point();
        r += (   cube(t)                     )/6.0 * _d->point();
        break;
    case Bezier: {
        double b0, b1, b2, b3;
        if (_d) {
            bernstein(t, b0, b1, b2, b3);
        } else {
            bernstein(t, b0, b1, b2);
        }
        r += b0 * _a->point();
        r += b1 * _b->point();
        r += b2 * _c->point();
        if (_d)
            r+= b3 * _d->point();
    }
    }
    return r;

}
