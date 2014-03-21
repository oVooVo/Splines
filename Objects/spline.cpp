#include "spline.h"
#include <QPainter>
#include "Spline/bezierpiece.h"
#include <QDebug>
#include <QMatrix3x3>
#include "Attributes/typeattribute.h"
#include "Spline/linearpiece.h"
#include "Attributes/boolattribute.h"

REGISTER_DEFN_TYPE(Object, Spline);

Spline::Spline(Object *parent) : PointObject(parent)
{
    QStringList splineTypes;
    splineTypes << "Linear" << "Cubic" << "B-Spline" << "Bezier";
    addAttribute("SplineType", new TypeAttribute("Spline type:", splineTypes));
    addAttribute("Closed", new BoolAttribute("Closed", false));
}

void Spline::serialize(QDataStream &stream) const
{
    PointObject::serialize(stream);
}

QPointF Spline::at(qreal t) const
{
    bool isClosed = ((BoolAttribute*) attributes()["Closed"])->value();

    int n = points().size();
    if (n < 2) return QPointF();

    //if (n < 3) isClosed = false;

    if (isClosed) n += 1;

    t *= n;
    int left = (int) t;
    t -= left;

    if (left >= n - 1)
        return isClosed ? points().first()->point() : points().last()->point();

    int right = left + 1;
    right %= points().size();


    int type = ((TypeAttribute*) attributes()["SplineType"])->currentIndex();
    switch (type) {
    case 0:     // linear
        return LinearPiece(points()[left], points()[right])(t);
    case 1:     // cubic
        break;
    case 2:     // b-spline
        break;
    case 3:     // bezier
        return BezierPiece(points()[left], points()[right])(t);
    }
    return QPointF();
}

Spline::Type Spline::type() const
{
    switch (((TypeAttribute*) attributes()["SplineType"])->currentIndex()) {
    case 0: return Spline::Linear;
    case 1: return Spline::Cubic;
    case 2: return Spline::BSpline;
    case 3: return Spline::Bezier;
    default: return Invalid;
    }
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
        p->setShowTangents(isSelected() && type() == Bezier);
        p->draw(painter);
    }

    Object::drawIndividual(painter);
}
