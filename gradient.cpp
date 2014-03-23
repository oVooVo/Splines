#include "gradient.h"

Gradient::Gradient() :
    QLinearGradient(QPointF(0, 0), QPointF(0, 1))
{
}

Gradient::Gradient(QColor start, QColor end) :
    QLinearGradient(QPointF(0, 0), QPointF(0, 1))
{
    setColorAt(0, start);
    setColorAt(1, end);
}
