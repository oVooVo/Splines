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
    Spline(QDataStream& stream);
    ~Spline();
    QPointF operator() (qreal t) const { return at(t); }
    QPointF at(qreal t) const;

public:
    void select(QPointF globalePosition, bool extend = false);
    void moveSelected(QPointF t);
    void removeSelected();
    void drawIndividual(QPainter &painter);
    void insert(QPointF globalePos);
    void remove(QPointF globalePos);
    void serialize(QDataStream &stream) const;


private:
    QList<Point*> _points;
    QList<Point*> _selected;
    static const qreal EPS;
    void handleSelection(Point* p, bool extended);
    void select(Point* p)   { p->select();   _selected.append(p);    }
    void deselect(Point* p) { p->deselect(); _selected.removeAll(p); }
    void deselectAll() { for (Point* p : _selected) deselect(p); }
    REGISTER_DECL_OBJECTTYPE(Spline);
};

#endif // SPLINE_H
