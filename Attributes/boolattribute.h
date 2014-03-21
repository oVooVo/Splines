#ifndef BOOLATTRIBUTE_H
#define BOOLATTRIBUTE_H

#include "attribute.h"

class BoolAttribute : public Attribute
{
    Q_OBJECT
public:
    BoolAttribute(QString label = "Label: ", bool value = false);
    bool value() const { return _value != 0; }
public slots:
    void setValue(bool value);

protected:
    void registerAttributeData(QDataStream &stream, Direction direction);
private:
    quint8 _value;

    REGISTER_DECL_TYPE(Attribute, BoolAttribute);
};

#endif // BOOLATTRIBUTE_H
