#include "attribute.h"
#include "transformationattribute.h"
#include <QDebug>

Attribute::Attribute()
{
}

void Attribute::serialize(QDataStream &out) const
{
    out << QString(metaObject()->className());
}

Attribute* Attribute::deserialize(QDataStream &in)
{
    QString classname;
    in >> classname;

    if (classname == "Attribute") return new Attribute(in);
    else if (classname == "TransformationAttribute") return new TransformationAttribute(in);
    //else if...
    qWarning() << "Warning: Classname " << classname << "not found. In Attributes";
    return 0;
}

QDataStream& operator<<(QDataStream& out, const Attribute* a)
{
    a->serialize(out);
    return out;
}

QDataStream& operator>>(QDataStream& in, Attribute* &a)
{
    a = Attribute::deserialize(in);
    return in;
}
