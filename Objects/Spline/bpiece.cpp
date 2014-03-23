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
    return QPointF();
}


/*
 *    if (!_d) {
        qreal b0, b1, b2;
        bernstein(t, b0, b1, b2);
        return b0 * _a->point() + b1 * _b->point() + b2 * _c->point();
    } else if (t < 0) {
        t++;

    } else if (t > 1) {
        t--;
    } else {
        QPointF r;
        r += cube(1 - t)/6.0 * _a->point();
        r += (3*cube(t) - 6*sqr(t) + 4)/6.0 * _b->point();
        r += (-3*cube(t) + 3*sqr(t) + 3*t + 1)/6.0 * _c->point();
        r += cube(t)/6.0 * _d->point();
        return r;
    }
    return QPointF();
    */
