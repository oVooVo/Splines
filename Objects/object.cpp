#include "object.h"
#include <QVariant>

Object::Object(Object *parent) : QObject(parent)
{
    _name = genericName();
}

Object::~Object()
{
}

void Object::setId(quint64 id)
{
    Q_ASSERT_X(_id == 0, "Object::setId", "Trying to set ID twice");
    _id = id;
    _name = genericName();
}

void Object::draw(QPainter &painter)
{
    Q_UNUSED(painter);
}

QList<Object*> Object::children() const
{
    QList<Object*> cs;
    for (QObject* c : QObject::children()) {
        cs.append((Object*) c);
    }
    return cs;
}

Object* Object::parent() const
{
    return (Object*) QObject::parent();
}

void Object::setParent(Object *parent)
{
    QObject::setParent(parent);
}

void Object::addChild(Object* child)
{
    if (child) {
        child->setParent(this);
    }
}

QString Object::genericName() const
{
    return QString("%1 <%2>").arg(metaObject()->className()).arg(id());
}


Object* Object::child(int row) const
{
    return children()[row];
}

int Object::childCount() const
{
    return children().size();
}

int Object::columnCount() const
{
    return 1;
}

QVariant Object::data(int column) const
{
    switch (column) {
    case 0:     return _name;
    default:    return QString("###");
    }

    return name();
}

int Object::row() const
{
    if (parent()) {
        return parent()->children().indexOf(const_cast<Object*>(this));
    } else {
        return 0;
    }
}







