#ifndef BPIECE_H
#define BPIECE_H

#include "point.h"
#include "splinepiece.h"

class BPiece : public SplinePiece
{
public:
    enum Type { Start, End, Middle, Bezier };
    BPiece(Point* a, Point* b, Point* c, Point* d, Type type = Middle);
    QPointF operator ()(double t) const;

private:
    Point* _a;
    Point* _b;
    Point* _c;
    Point* _d;
    Type _type;
};



#endif // BPIECE_H
