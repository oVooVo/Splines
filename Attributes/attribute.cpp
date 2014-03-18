#include "attribute.h"
#include "transformationattribute.h"
#include <QDebug>

ATTRIBUTE_CREATOR_MAP_TYPE *Attribute::_creatorMap = 0;

Attribute::Attribute()
{
}

void Attribute::serialize(QDataStream &out) const
{
    out << QString(metaObject()->className());
}

Attribute* Attribute::deserialize(QDataStream &stream)
{
    QString classname;
    stream >> classname;

    Attribute* attribute = createInstance(classname, stream);
    if (!attribute) {
        qWarning() << "Warning: Classname " << classname << "not found.";
        Q_ASSERT_X(attribute, "Attribute::deserialize", "deserialization failed.");
    }
    return attribute;
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

Attribute *Attribute::createInstance(QString className, QDataStream& stream)
{
    if (!_creatorMap)
    {
        _creatorMap = new ATTRIBUTE_CREATOR_MAP_TYPE();
    }

    ATTRIBUTE_CREATOR_MAP_TYPE::iterator it = _creatorMap->find(className);
    if (it == _creatorMap->end())
        return 0;

    return (it.value())(stream);
}

