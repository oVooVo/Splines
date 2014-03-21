#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include <QPainter>

class Point
{
public:
    enum Tangent { LeftTangent, RightTangent };
    explicit Point(qreal x, qreal y) { _point = QPointF(x, y); }
    explicit Point(QPointF point);
    void setTangent(QPointF left, QPointF right);
    QPointF leftTangent() const { return _left; }
    QPointF rightTangent() const { return _right; }
    QPointF tangent(Tangent tangent) const { return (tangent == LeftTangent ? _left : _right); }
    QPointF leftTangentGlobal() const { return _left + _point; }
    QPointF rightTangentGlobal() const { return _right + _point; }
    void setPoint(QPointF p);
    QPointF point() const { return _point; }
    void draw(QPainter &painter);
    void setShowTangents(bool show) { _showTangents = show; }
    bool tangentsShown() const { return _showTangents; }
    void select() { _select = true; }
    void deselect() { _select = false; }
    bool isSelected() const { return _select; }
    void move(QPointF t);

private:
    QPointF _left;
    QPointF _right;
    QPointF _point;
    bool _showTangents = false;
    bool _select = false;

protected:
    friend QDataStream& operator<<(QDataStream& out, const Point* s);
    friend QDataStream& operator>>(QDataStream& in, Point* &s);


};

QDataStream& operator<<(QDataStream& out, const Point* s);
QDataStream& operator>>(QDataStream& in, Point* &s);

#endif // POINT_H
