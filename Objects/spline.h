#ifndef SPLINE_H
#define SPLINE_H

#include "Objects/Spline/splinepiece.h"
#include "object.h"
#include "Objects/pointobject.h"
#include <QList>

class Spline : public PointObject
{
    Q_OBJECT
public:
    enum Type { Linear, Cubic, BSpline, Bezier, Invalid };
    Spline(Object* parent = 0);
    QPointF operator() (double t) const { return at(t); }
    QPointF at(double t) const;
    Type type() const;

    int segment(double t) const;
    int segments() const;
    bool isClosed() const;

public:
    void drawIndividual(QPainter &painter);
    void serialize(QDataStream &stream) const;



private:
    REGISTER_DECL_TYPE(Object, Spline);
};

#endif // SPLINE_H
