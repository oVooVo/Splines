#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QColorDialog>

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorButton(QWidget *parent = 0);
    QColor color() const { return _color; }
    void setColor(QColor color) { _color = color; }

protected:
    void paintEvent(QPaintEvent *);

signals:
    void colorChanged(QColor);

private:
    QColor _color = QColor();
    QString _label = "";

};

#endif // COLORBUTTON_H
