#include "object.h"
#include <QVariant>
#include "spline.h"
#include <QDebug>
#include "root.h"
#include "spline.h"
#include <QPainter>
#include <QMetaObject>

Object::Object(Object *parent) : QObject(parent)
{
    _name = genericName();
    initAttributes();
}

Object::Object(QDataStream &stream)
{
    stream >> _name;
    stream >> _id;
    stream >> _attributes;
    for (Attribute* a : _attributes) {
        connect(a, SIGNAL(changed()), this, SIGNAL(changed()));
    }

    QList<Object*> children;
    stream >> children;
    for (Object* o : children) {
        o->setParent(this);
    }
}

void Object::serialize(QDataStream &stream) const
{
    //class name
    stream << QString(metaObject()->className());

    //object attributes
    stream << name();
    stream << id();
    stream << _attributes;

    stream << children();
}

Object* Object::deserialize(QDataStream &stream)
{
    QString classname;
    stream >> classname;

    if (classname == "Object") return new Object(stream);
    else if (classname == "Root") return new Root(stream);
    else if (classname == "Spline") return new Spline(stream);
    qWarning() << "Warning: Classname " << classname << "not found.";
    return 0;
}

void Object::initAttributes()
{
    addAttribute("TransformationAttribute", new TransformationAttribute());
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
    painter.save();
    painter.setTransform(localeTransform(), true);
    painter.save();
    drawIndividual(painter);
    painter.restore();
    for (Object* c : children())
        c->draw(painter);
    painter.restore();

}

void Object::drawIndividual(QPainter &painter)
{
    QPen pen;
    pen.setCosmetic(true);
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(QPointF(0, 0), QPointF(0, 3));
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPointF(0, 0), QPointF(3, 0));
    pen.setColor(Qt::black);
    painter.drawEllipse(QPointF(), 1, 1);
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
    if (Object::parent())
        disconnect(this, SIGNAL(changed()), parent, SIGNAL(changed()));
    QObject::setParent(parent);
    if (Object::parent()) {
        connect(this, SIGNAL(changed()), parent, SIGNAL(changed()));
    }
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

QTransform Object::globaleTransform() const
{
    if (!parent()) return localeTransform();
    return localeTransform() * parent()->globaleTransform();
}

QPointF Object::map(QPointF pos, bool translate) const
{
    QTransform trans = globaleTransform().inverted();
    if (!translate)
        trans = QTransform(trans.m11(), trans.m12(), 0, trans.m21(), trans.m22(), 0, 0, 0, 1);
    return trans.map(pos);
}

void Object::insert(QPointF globalePos)
{
    Q_UNUSED(globalePos);
}

void Object::remove(QPointF globalePos)
{
    Q_UNUSED(globalePos);
}

void Object::select(QPointF globalePos, bool extended)
{
    Q_UNUSED(globalePos);
    Q_UNUSED(extended);
}

void Object::moveSelected(QPointF t)
{
    Q_UNUSED(t);
}

QStringList Object::attributeKeys(QString classname)
{

    auto con = [](QStringList l1, QStringList l2) {
        l1.append(l2);
        return l1;
    };

    QStringList object, spline, root;
    object << "TransformationAttribute";

    if (classname == "Object") return object;
    if (classname == "Spline")
        return con(object, spline);
    if (classname == "Root")
        return con(object, root);
    Q_ASSERT_X(false, "Object::attributeKeys", "undefined object");
    return QStringList();
}

void Object::addAttribute(QString key, Attribute *a)
{
    Q_ASSERT_X(!_attributes.contains(key), "Object::addAttribute", "Multiple key");
    _attributes.insert(key, a);
    connect(a, SIGNAL(changed()), this, SIGNAL(changed()));
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


