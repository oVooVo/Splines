#ifndef COLORATTRIBUTE_H
#define COLORATTRIBUTE_H

#include "attribute.h"
#include <QColor>

class ColorAttribute : public Attribute
{
    Q_OBJECT
public:
    ColorAttribute(QString label = "Label: ", QColor value = QColor());
    QColor color() const;
    QString toString() const;
    void fromString(QString string);


public slots:
    void setColor(QColor color);


private:
    QColor _color;

    REGISTER_DECL_TYPE(Attribute, ColorAttribute);
};

#endif // COLORATTRIBUTE_H
