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
    Spline(Object* parent = 0);
    QPointF operator() (qreal t) const { return at(t); }
    QPointF at(qreal t) const;

public:
    /*
    void select(QPointF globalePosition, bool extend = false);
    void moveSelected(QPointF t);
    void removeSelected();
    void insert(QPointF globalePos);
    void remove(QPointF globalePos);
    */

    void drawIndividual(QPainter &painter);
    void serialize(QDataStream &stream) const;



private:
    REGISTER_DECL_TYPE(Object, Spline);
};

#endif // SPLINE_H
