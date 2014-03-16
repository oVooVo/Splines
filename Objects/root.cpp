#include "root.h"

Root::Root(Root *parent) : Object(parent)
{
}

Root::Root(QDataStream &stream) : Object(stream)
{
    Q_UNUSED(stream);
}

void Root::serialize(QDataStream &stream) const
{
    Object::serialize(stream);
}
