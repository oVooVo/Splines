#include "stringattribute.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Attribute, StringAttribute);

StringAttribute::StringAttribute(QString label, QString string) : Attribute(label)
{
    _string = string;
}

void StringAttribute::setString(const QString &string)
{
    if (string == _string) return;

    beforeChange();
    _string = string;
    emit changed();
}

void StringAttribute::registerAttributeData(QDataStream &stream, Direction direction)
{
    REGISTER_DATA(_string)
}

void StringAttribute::fromString(QString string)
{
    setString(string);
}

QString StringAttribute::toString() const
{
    return string();
}
