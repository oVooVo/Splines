#include "splinepiece.h"

SplinePiece::SplinePiece()
{
}

void bernstein(const qreal x, qreal &b0, qreal &b1, qreal &b2, qreal &b3)
{
    qreal x2 = x*x;
    qreal x3 = x2*x;

    b0 = 1 - 3*x + 3*x2 - x3;
    b1 = 3*x - 6*x2 + 3*x3;
    b2 = 3*x2 - 3*x3;
    b3 = x3;
}

void bernstein(const qreal x, qreal &b0, qreal &b1, qreal &b2)
{
    qreal x2 = x*x;

    b0 = x2-2*x+1;
    b1 = 2*x -2* x2;
    b2 = x2;
}

double cube(double x) { return x*x*x; }
double sqr(double x) { return x*x; }
