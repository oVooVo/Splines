#include "colorbutton.h"
#include <QPainter>
#include <QDebug>

ColorButton::ColorButton(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, &QPushButton::clicked,
            [this]() {
        QColor color = QColorDialog::getColor(_color, this, QString("%1 color").arg(text()));
        if (color.isValid()) {
            if (_color != color) {
                _color = color;
                emit colorChanged(color);
                update();
            }
        }
    });
}

void ColorButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), _color);
}

