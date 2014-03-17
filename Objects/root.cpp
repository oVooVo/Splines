#include "root.h"
#include <QDebug>

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

void Root::draw(QPainter &painter)
{
    Object::draw(painter);
}
