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
    void setColor(QColor color) { _color = color; _multiState = false; }
    void setMulti() { _multiState = true; setText("Multi"); }

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void colorChanged(QColor);

private:
    QColor _color = QColor();
    QString _label = "";
    bool _multiState = false;

};

#endif // COLORBUTTON_H
