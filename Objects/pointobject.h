#ifndef POINTOBJECT_H
#define POINTOBJECT_H

#include "object.h"
#include "point.h"

class PointObject : public Object
{
    Q_OBJECT
public:
    PointObject(Object* parent = 0);
    virtual ~PointObject();

    virtual void addPoint(Point* p);

protected:
    QList<Point*> points() const { return _points; }
    QList<Point*> selection() const { return _selected; }
    virtual void serialize(QDataStream &stream) const;
    virtual void deserialize(QDataStream &stream);

private:
    QList<Point*> _points;
    QList<Point*> _selected;
    static const qreal EPS;
/*
    void handleSelection(Point* p, bool extended);
    void select(Point* p)   { p->select();   _selected.append(p);    }
    void deselect(Point* p) { p->deselect(); _selected.removeAll(p); }
    void deselectAll() { for (Point* p : _selected) deselect(p); }
    */
};

#endif // POINTOBJECT_H
