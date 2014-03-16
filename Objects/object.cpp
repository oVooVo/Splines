#include "object.h"
#include <QVariant>
#include "spline.h"
#include <QDebug>
#include "root.h"
#include "spline.h"

Object::Object(Object *parent) : QObject(parent)
{
    _name = genericName();
}

Object::Object(QDataStream &stream)
{
    stream >> _name;
    stream >> _id;
    QList<Object*> children;
    stream >> children;
    for (Object* o : children) {
        o->setParent(this);
    }
}

Object::~Object()
{
    qDebug() << "delete" << this << name();
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

void Object::addChild(Object* child, int pos)
{
    if (!child) return;
    if (pos == -1) {
        child->setParent(this);
    } else {
        QList<Object*> childs;
        blockSignals(true);
        for (Object* c : children()) {
            c->setParent(0);
            childs << c;
        }
        childs.insert(pos, child);
        for (Object* c : children()) {
            if (c == child) {
                blockSignals(false);
                c->setParent(this);
                blockSignals(true);
            }
            c->setParent(this);
        }
        blockSignals(false);
    }
}

QString Object::genericName() const
{
    return QString("%1 <%2>").arg(metaObject()->className()).arg(id());
}


Object* Object::child(int row) const
{
    if (row >= childCount() || row < 0) return 0;
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

bool Object::removeChildren(int position, int count)
{
    if (position < 0 || position + count > children().size())
        return false;

    for (int row = 0; row < count; ++row)
        delete children()[position];

    return true;
}

void Object::serialize(QDataStream &stream) const
{
    //class name
    stream << QString(metaObject()->className());

    //object attributes
    stream << name();
    stream << id();
    stream << children();
}

Object* Object::deserialize(QDataStream &stream)
{
    QString classname;
    stream >> classname;

    qDebug() << "deserialize: " << classname;

    if (classname == "Object") return new Object(stream);
    else if (classname == "Root") return new Root(stream);
    else if (classname == "Spline") return new Spline(stream);
    qDebug() << "Warning: Classname " << classname << "not found.";
    return 0;
}

QDataStream& operator<<(QDataStream& stream, const Object* o)
{
    o->serialize(stream);
    return stream;
}

QDataStream& operator>>(QDataStream& stream, Object* &o)
{
    o = Object::deserialize(stream);
    return stream;
}


