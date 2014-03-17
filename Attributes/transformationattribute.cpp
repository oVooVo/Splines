#include "transformationattribute.h"
#include <qmath.h>

TransformationAttribute::TransformationAttribute()
{
    _x = 0;
    _y = 0;
    _sx = 1;
    _sy = 1;
    _r = 0;
    connect(this, SIGNAL(rChanged(qreal)), this, SIGNAL(changed()));
    connect(this, SIGNAL(xChanged(qreal)), this, SIGNAL(changed()));
    connect(this, SIGNAL(yChanged(qreal)), this, SIGNAL(changed()));
    connect(this, SIGNAL(sxChanged(qreal)), this, SIGNAL(changed()));
    connect(this, SIGNAL(syChanged(qreal)), this, SIGNAL(changed()));
}

TransformationAttribute::TransformationAttribute(QDataStream &stream) : Attribute(stream)
{
    stream >> _x >> _y >> _sx >> _sy >> _r;
}

void TransformationAttribute::serialize(QDataStream &out) const
{
    Attribute::serialize(out);
    out << _x << _y << _sx << _sy << _r;
}

QTransform TransformationAttribute::value() const
{
    return QTransform(
                _sx * qCos(_r), -_sy * qSin(_r), 0,
                _sx * qSin(_r),  _sy * qCos(_r), 0,
                _x,              _y,             1
                );
}

void TransformationAttribute::setX(qreal x)
{
    if (_x == x) return;
    _x = x;
    emit xChanged(_x);
}

void TransformationAttribute::setY(qreal y)
{
    if (_y == y) return;
    _y = y;
    emit yChanged(_y);
}

void TransformationAttribute::setSX(qreal sx)
{
    if (_sx == sx) return;
    _sx = sx;
    emit sxChanged(_sx);
}

void TransformationAttribute::setSY(qreal sy)
{
    if (_sy == sy) return;
    _sy = sy;
    emit syChanged(_sy);
}

void TransformationAttribute::setR(qreal r)
{
    if (_r == r) return;
    _r = r;
    emit rChanged(_r);
}

qreal TransformationAttribute::value(Key k) const
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


