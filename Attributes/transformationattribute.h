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
    void makeConnects();

    QTransform value() const;
    void setValue(QTransform t);

    qreal r() const { return _r * 180 * M_1_PI; }
    qreal x() const { return _x; }
    qreal y() const { return _y; }
    qreal sx() const { return _sx; }
    qreal sy() const { return _sy; }
    qreal value(Key k) const;

public slots:
    void setX(double x);
    void setY(double y);
    void setSX(double sx);
    void setSY(double sy);
    void setR(double r);

signals:
    void xChanged(double);
    void yChanged(double);
    void sxChanged(double);
    void syChanged(double);
    void rChanged(double);

private:
    double _x;
    double _y;
    double _sx;
    double _sy;
    double _r;
    REGISTER_DECL_ATTRIBUTETYPE(TransformationAttribute);

};

#endif // TRANSFORMATIONATTRIBUTE_H
