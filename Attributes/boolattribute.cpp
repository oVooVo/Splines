#include "boolattribute.h"

REGISTER_DEFN_TYPE(Attribute, BoolAttribute);

BoolAttribute::BoolAttribute(QString label, bool value) : Attribute(label)
{
    _value = value;
}

void BoolAttribute::registerAttributeData(QDataStream &stream, Direction direction)
{
    REGISTER_DATA(_value);
}

void BoolAttribute::setValue(bool value)
{
    if (value == _value) return;

    _value = value;
    emit changed();
}

QString BoolAttribute::toString() const
{
    return _value ? "true" : "false";
}

void BoolAttribute::fromString(QString string)
{
    if (string.toUpper() == QString("true").toUpper()) {
        setValue(true);
    } else {
        setValue(false);
    }
}
