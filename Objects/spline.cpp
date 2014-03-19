#include "spline.h"
#include <QPainter>
#include "Spline/bezierpiece.h"
#include <QDebug>
#include <QMatrix3x3>
#include "Attributes/typeattribute.h"

REGISTER_DEFN_OBJECTTYPE(Spline);

Spline::Spline(Object *parent) : PointObject(parent)
{
    QStringList splineTypes;
    splineTypes << "Linear" << "Cubic" << "B-Spline" << "Bezier";
    addAttribute("SplineType", new TypeAttribute("Spline type:", splineTypes));
}

void Spline::serialize(QDataStream &stream) const
{
    PointObject::serialize(stream);
}

QPointF Spline::at(qreal t) const
{
    int n = points().size();
    if (n < 2) return QPointF();

    t *= n;
    int left = (int) t;
    t -= left;

    if (left >= n - 1)
        return points().last()->point();

    BezierPiece piece(points()[left], points()[left + 1]);
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
    for (Point* p : points()) {
        p->draw(painter);
    }

    Object::drawIndividual(painter);
}
