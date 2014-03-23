#ifndef CUBICPIECE_H
#define CUBICPIECE_H

#include "splinepiece.h"

class CubicPiece : public SplinePiece
{
public:
    CubicPiece(Point* a, Point* b, Point* c, Point* d);
    QPointF operator ()(double t) const;

private:
    Point* _a;
    Point* _b;
    Point* _c;
    Point* _d;
};


#endif // CUBICPIECE_H
