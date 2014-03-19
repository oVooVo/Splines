#include "root.h"
#include <QDebug>


REGISTER_DEFN_OBJECTTYPE(Root);

Root::Root(Root *parent) : Object(parent)
{
}

void Root::drawIndividual(QPainter &painter)
{
    Object::drawIndividual(painter);
}
