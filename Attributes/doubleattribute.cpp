#include "doubleattribute.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Attribute, DoubleAttribute);

DoubleAttribute::DoubleAttribute(QString label, double value) : Attribute(label)
{
    _value = value;
}

void DoubleAttribute::fromString(QString string)
{
    bool ok;
    setValue(string.toDouble(&ok));
    if (!ok)
        qWarning() << "cannot parse " << string;
}

QString DoubleAttribute::toString() const
{
    return QString("%1").arg(value());
}

void DoubleAttribute::setValue(double v)
{
    if (_value == v) return;

    _value = v;
    emit changed();
}
