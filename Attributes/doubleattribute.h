#ifndef DOUBLEATTRIBUTE_H
#define DOUBLEATTRIBUTE_H

#include "attribute.h"

class DoubleAttribute : public Attribute
{
    Q_OBJECT
public:
    DoubleAttribute(QString label = "Label: ", double value = 0.0);
    void fromString(QString string);
    QString toString() const;
    double value() const { return _value; }
public slots:
    void setValue(double v);
private:
    double _value;
    REGISTER_DECL_TYPE(Attribute, DoubleAttribute);

};

#endif // DOUBLEATTRIBUTE_H
