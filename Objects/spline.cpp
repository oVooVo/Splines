#include "spline.h"
#include <QPainter>
#include "Spline/bezierpiece.h"
#include <QDebug>
#include <QMatrix3x3>
#include "Attributes/typeattribute.h"
#include "Spline/linearpiece.h"
#include "Attributes/boolattribute.h"
#include "Spline/splinepiece.h"
#include "Spline/bpiece.h"
#include "Spline/cubicpiece.h"
#include "preferences.h"
#include <QVector4D>
#include "Attributes/colorattribute.h"


REGISTER_DEFN_TYPE(Object, Spline);

Spline::Spline(Object *parent) : PointObject(parent)
{
    QStringList splineTypes;
    splineTypes << "Linear" << "Bezier";
    addAttribute("SplineType", new TypeAttribute("Spline type:", splineTypes));
    addAttribute("Closed", new BoolAttribute("Closed", false));
}

void Spline::serialize(QDataStream &stream) const
{
    PointObject::serialize(stream);
}

bool Spline::isClosed() const
{
    return ((BoolAttribute*)attributes()["Closed"])->value();
}

int Spline::segment(double t) const
{
    if (t < 0) return 0;
    if (t >= 1) return (segments() - 1);
    return (int) (t * segments());
}

int Spline::segments() const
{
    int n = points().size();
    if (n == 0) return 0;

    switch (type()) {
    case Linear:
    case Bezier:
        return isClosed() ? n : n - 1;
    case BSpline:
    case Cubic:
        if (isClosed()) {
            return 0;
        } else {
            if (n < 2) return 0;
            if (n == 2) return 1;
            if (n == 3) return 1;
            return n - 3;
        }
    case Invalid:
    default:
        return 0;
    }
}


QPointF Spline::at(double t) const
{
    if (segments() < 1) return QPointF();

    double u = t * segments() - segment(t);

    int a = segment(t) % points().size();
    int b = (a+1) % points().size();

    switch (type()) {
    case Linear:
        return LinearPiece(points()[a], points()[b])(u);
    case Bezier:
        return BezierPiece(points()[a], points()[b])(u);
    case BSpline:
    case Cubic:
    case Invalid:
    default:
        return QPointF();
    }

}

Spline::Type Spline::type() const
{
    switch (((TypeAttribute*) attributes()["SplineType"])->currentIndex()) {
    case 0: return Spline::Linear;
    case 1: return Spline::Bezier;
    case 2: return Spline::Cubic;
    case 3: return Spline::BSpline;
    default: return Invalid;
    }
}

QColor lerp(QColor a, QColor b, double t)
{
    QVector4D av = QVector4D(a.red(), a.green(), a.blue(), a.alpha());
    QVector4D bv = QVector4D(b.red(), b.green(), b.blue(), b.alpha());
    QVector4D l = t * av + (1-t) * bv;
    return QColor(l.x(), l.y(), l.z(), l.w());
}

void Spline::drawIndividual(QPainter &painter)
{
    QPen pen;
    pen.setCosmetic(true);
    painter.setPen(pen);
    int n = 100;
    for (int i = 0; i <= n; i++) {
        if (isSelected())
            painter.setPen(
                        lerp(
                            Preferences::value<ColorAttribute>("colors.spline.active.start")->color(),
                            Preferences::value<ColorAttribute>("colors.spline.active.end")->color(),
                            (double) i / n
                    ));
        else painter.setPen(Preferences::value<ColorAttribute>("colors.spline.inactive")->color());
        painter.drawLine(at(i/(n + 1.0)), at((i+1.0)/(n+1.0)));
    }
    for (Point* p : points()) {
        p->setShowTangents(isSelected() && type() == Bezier);
        p->draw(painter);
    }

    Object::drawIndividual(painter);
}
