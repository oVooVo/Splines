#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include <QPainter>

class Point
{
public:
    enum Tangent { NoTangent = 0x0, LeftTangent = 0x1, RightTangent = 0x2 };
    enum TangentMode { Simultan, Single };

    explicit Point(qreal x, qreal y) { _point = QPointF(x, y); }
    explicit Point(QPointF point);

    void setPoint(QPointF p);
    QPointF point() const { return _point; }

    void setTangent(QPointF left, QPointF right);
    QPointF leftTangent() const { return _left + _point; }
    QPointF rightTangent() const { return _right + _point; }
    QPointF left() const { return _left; }
    QPointF right() const { return _right; }
    QPointF tangent(Tangent tangent) const { return (tangent == LeftTangent ?
                                                       leftTangent() :
                                                       rightTangent()  ); }
    void setShowTangents(bool show) { _showTangents = show; }
    bool tangentsShown() const { return _showTangents; }

    void select() { _isSelected = true; }
    void deselect() { _isSelected = false; }
    void selectTangent(Tangent tangent);
    Tangent selectedTangent() const { return _selectedTangent; }
    bool isSelected() const { return _isSelected; }

    void move(QPointF t);
    void moveTangent(QPointF t, TangentMode mode);

    void draw(QPainter &painter);

private:
    QPointF _left;
    QPointF _right;
    QPointF _point;
    Tangent _selectedTangent = NoTangent;
    bool _showTangents = false;
    bool _isSelected = false;

protected:
    friend QDataStream& operator<<(QDataStream& out, const Point* s);
    friend QDataStream& operator>>(QDataStream& in, Point* &s);
};

struct Polar {
    qreal r;
    qreal phi;
} typedef Polar;

QDataStream& operator<<(QDataStream& out, const Point* s);
QDataStream& operator>>(QDataStream& in, Point* &s);

#endif // POINT_H
