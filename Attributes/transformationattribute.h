#ifndef TRANSFORMATIONATTRIBUTE_H
#define TRANSFORMATIONATTRIBUTE_H

#include <QObject>
#include <QTransform>
#include <QDataStream>

#include "attribute.h"

class TransformationAttribute : public Attribute
{
    Q_OBJECT
public:
    enum Key { R, X, Y, SX, SY, Key_first = R, Key_last = SY };
    TransformationAttribute();
    TransformationAttribute(QDataStream &stream);
    void serialize(QDataStream &out) const;

    QTransform value() const;

    qreal r() const { return _r; }
    qreal x() const { return _x; }
    qreal y() const { return _y; }
    qreal sx() const { return _sx; }
    qreal sy() const { return _sy; }
    qreal value(Key k) const;

public slots:
    void setX(qreal x);
    void setY(qreal y);
    void setSX(qreal sx);
    void setSY(qreal sy);
    void setR(qreal r);

signals:
    void xChanged(qreal);
    void yChanged(qreal);
    void sxChanged(qreal);
    void syChanged(qreal);
    void rChanged(qreal);

private:
    qreal _x;
    qreal _y;
    qreal _sx;
    qreal _sy;
    qreal _r;

};

#endif // TRANSFORMATIONATTRIBUTE_H
