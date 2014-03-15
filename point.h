#ifndef POINT_H
#define POINT_H

#include <QPointF>

class Point
{
public:
    explicit Point(qreal x, qreal y) { _point = QPointF(x, y); }
    explicit Point(QPointF point) { _point = point; }
    void setTangent(QPointF left, QPointF right);
    QPointF leftTangent() const { return _left; }
    QPointF rightTangent() const { return _right; }
    QPointF leftTangentGlobal() const { return _left + _point; }
    QPointF rightTangentGlobal() const { return _right + _point; }
    QPointF point() const { return _point; }

private:
    QPointF _left;
    QPointF _right;
    QPointF _point;
};

#endif // POINT_H
