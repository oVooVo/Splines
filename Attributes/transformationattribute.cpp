#include "transformationattribute.h"
#include <qmath.h>
#include <QDebug>

REGISTER_DEFN_TYPE(Attribute, TransformationAttribute);

TransformationAttribute::TransformationAttribute(QString label) : Attribute(label)
{
    _x = 0;
    _y = 0;
    _sx = 1;
    _sy = 1;
    _r = 0;
    connect(this, SIGNAL(rChanged(double)), this, SIGNAL(changed()));
    connect(this, SIGNAL(xChanged(double)), this, SIGNAL(changed()));
    connect(this, SIGNAL(yChanged(double)), this, SIGNAL(changed()));
    connect(this, SIGNAL(sxChanged(double)), this, SIGNAL(changed()));
    connect(this, SIGNAL(syChanged(double)), this, SIGNAL(changed()));
}

void TransformationAttribute::registerAttributeData(QDataStream &stream, Direction direction)
{
    REGISTER_DATA(_x)
    REGISTER_DATA(_y)
    REGISTER_DATA(_sx)
    REGISTER_DATA(_sy)
    REGISTER_DATA(_r)
}

QTransform TransformationAttribute::value() const
{
    return QTransform(
                _sx * qCos(_r), _sx * qSin(_r), 0,
               -_sy * qSin(_r), _sy * qCos(_r), 0,
                _x,              _y,            1
                );
}

void TransformationAttribute::setX(double x)
{
    if (_x == x) return;
    _x = x;
    emit xChanged(_x);
}

void TransformationAttribute::setY(double y)
{
    if (_y == y) return;
    _y = y;
    emit yChanged(_y);
}

void TransformationAttribute::setSX(double sx)
{
    if (_sx == sx) return;
    _sx = sx;
    emit sxChanged(_sx);
}

void TransformationAttribute::setSY(double sy)
{
    if (_sy == sy) return;
    _sy = sy;
    emit syChanged(_sy);
}

void TransformationAttribute::setR(double r)
{
    r *= M_PI / 180.0;
    if (_r == r) return;
    _r = r;
    emit rChanged(_r);
}

double TransformationAttribute::value(Key k) const
{
    switch (k) {
    case R: return r();
    case X: return x();
    case Y: return y();
    case SX: return sx();
    case SY: return sy();
    }
    Q_ASSERT(false);
    return 0;
}

void TransformationAttribute::setValue(QTransform t)
{
    double m11 = t.m11();
    double m12 = t.m12();
    double m21 = t.m21();
    double m22 = t.m22();

    _sx = qSqrt(qPow(m11, 2) + qPow(m12, 2));
    _sy = qSqrt(qPow(m21, 2) + qPow(m22, 2));

    double r11  =  qAcos(m11 / _sx);
    double r12  =  qAsin(m12 / _sx);
    double r21  = -qAsin(m21 / _sy);
    double r22  =  qAcos(m22 / _sy);


//    double delta = qSqrt(qPow(r12 - r11, 2) + qPow(r21 - r11, 2) + qPow(r22 - r11, 2)
//                      + qPow(r11 - r12, 2) + qPow(r21 - r12, 2) + qPow(r22 - r12, 2)
//                      + qPow(r11 - r21, 2) + qPow(r12 - r21, 2) + qPow(r22 - r21, 2)
//                      + qPow(r11 - r22, 2) + qPow(r12 - r22, 2) + qPow(r21 - r22, 2));

    _r = (r11 + r12 + r21 + r22) / 4.0;
    _x = t.m31();
    _y = t.m32();

}

