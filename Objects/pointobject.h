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

    QList<Point*> points() const { return _points; }
    QList<Point*> selection() const { return _selected; }

protected:
    virtual void serialize(QDataStream &stream) const;
    virtual void deserialize(QDataStream &stream);

public:
    void selectAllPoints();
    void deselectAllPoints();
    void selectPoint(Point* p);
    void deselectPoint(Point* p);
    void toggleSelectionOfPoint(Point* p);
    void deleteSelectedPoints();
    Point* pointAt(const QPointF pos) const;
    Point* selectTangentAt(const QPointF pos) const;

private:
    QList<Point*> _points;
    QList<Point*> _selected;
};

#endif // POINTOBJECT_H
