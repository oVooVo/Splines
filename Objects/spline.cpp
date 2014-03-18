#include "spline.h"
#include <QPainter>
#include "Spline/bezierpiece.h"
#include <QDebug>
#include <QMatrix3x3>

const qreal Spline::EPS = 4.0;

REGISTER_DEFN_OBJECTTYPE(Spline);

Spline::Spline(Object *parent) : Object(parent)
{
}

Spline::Spline(QDataStream &stream) : Object(stream)
{
    stream >> _points;
    for (Point* p : _points)
        if (p->isSelected()) _selected.append(p);
}

void Spline::serialize(QDataStream &stream) const
{
    Object::serialize(stream);
    stream << _points;
}

Spline::~Spline()
{
    qDeleteAll(_points);
}

QPointF Spline::at(qreal t) const
{
    int n = _points.size();
    if (n < 2) return QPointF();

    t *= n;
    int left = (int) t;
    t -= left;

    if (left >= n - 1)
        return _points.last()->point();

    BezierPiece piece(_points[left], _points[left + 1]);
    return piece(t);
}

void Spline::drawIndividual(QPainter &painter)
{
    QPen p;
    p.setCosmetic(true);
    painter.setPen(p);
    int n = 100;
    for (int i = 0; i < n; i++) {
        painter.drawLine(at(i/(n + 1.0)), at((i+1.0)/(n+1.0)));
    }
    for (Point* p : _points) {
        p->draw(painter);
    }

    Object::drawIndividual(painter);
}

void Spline::handleSelection(Point *p, bool extended)
{
    if (!p->isSelected()) {
        if (!extended) {
            deselectAll();
        }
        select(p);
    } else {
        if (extended) {
            deselect(p);
        } else {
            deselectAll();
            select(p);
        }
    }
}

void Spline::select(QPointF globalePosition, bool extend)
{
    QPointF pos = map(globalePosition);
    if (_points.isEmpty()) return;
    Point* pressedPoint = _points.first();
    for (Point* p : _points) {
        if ((pos - p->point()).manhattanLength() < (pos - pressedPoint->point()).manhattanLength()) {
            pressedPoint = p;
        }
    }
    if ((pressedPoint->point() - pos).manhattanLength() < EPS)
        handleSelection(pressedPoint, extend);
    else if (!extend)
        deselectAll();
    emit changed();
}

void Spline::moveSelected(QPointF t)
{
    t = map(t, false);
    for (Point* p : _selected) {
        p->setPoint(p->point() + t);
    }
    emit changed();
}

void Spline::removeSelected()
{
    for (Point* p : _selected)
        _points.removeOne(p);
    qDeleteAll(_selected);
    _selected.clear();
    emit changed();
}

void Spline::insert(QPointF globalePos)
{
    Point* p = new Point(map(globalePos));
    _points.append(p);
    emit changed();
}

void Spline::remove(QPointF globalePos)
{
    QList<Point*> selection = _selected;
    deselectAll();
    select(globalePos, false);
    removeSelected();
    deselectAll(); // obsolete?
    for (Point* p : selection) {
        select(p);
    }
    emit changed();
}
