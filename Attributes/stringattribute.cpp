#include "stringattribute.h"
#include <QDebug>

REGISTER_DEFN_ATTRIBUTETYPE(StringAttribute);

StringAttribute::StringAttribute(QDataStream& stream) : Attribute(stream)
{
    stream >>_string >> _label;
}

StringAttribute::StringAttribute(QString label, QString string)
{
    _label = label;
    _string = string;
}

void StringAttribute::setString(const QString &string)
{
    if (string == _string) return;

    _string = string;
    emit changed();
}

void StringAttribute::setLabel(const QString &label)
{
    _label = label;
}

void StringAttribute::serialize(QDataStream &out) const
{
    Attribute::serialize(out);
    out << _string << _label;
}
