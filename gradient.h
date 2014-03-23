#ifndef GRADIENT_H
#define GRADIENT_H

#include <QLinearGradient>

class Gradient : public QLinearGradient
{
public:
    explicit Gradient();
    explicit Gradient(QColor start, QColor end);

};

#endif // GRADIENT_H
