#ifndef SPLINEPIECE_H
#define SPLINEPIECE_H

#include "point.h"
#include <QPointF>

class SplinePiece
{
public:
    SplinePiece();
    virtual QPointF operator() (double t) const = 0;
};

void bernstein(const qreal x, qreal &b0, qreal &b1, qreal &b2, qreal &b3);
void bernstein(const qreal x, qreal &b0, qreal &b1, qreal &b2);
double cube(double x);
double sqr(double x);

#endif // SPLINEPIECE_H
