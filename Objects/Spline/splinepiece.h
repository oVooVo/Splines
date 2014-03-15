#ifndef SPLINEPIECE_H
#define SPLINEPIECE_H

#include "point.h"
#include <QPointF>

class SplinePiece
{
public:
    SplinePiece();
    virtual QPointF operator() (qreal t) const = 0;
};

#endif // SPLINEPIECE_H
