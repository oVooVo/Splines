#ifndef SPLINE_H
#define SPLINE_H

#include "Objects/Spline/splinepiece.h"
#include "object.h"
#include <QList>

class Spline : public Object
{
    Q_OBJECT
public:
    Spline(Object* parent = 0);
    void addPiece(SplinePiece* p) { pieces << p; }
    QPointF operator() (qreal t) const;

private:
    QList<SplinePiece*> pieces;
};

#endif // SPLINE_H
