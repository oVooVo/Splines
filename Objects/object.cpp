#include "object.h"
#include <QVariant>
#include "spline.h"
#include <QDebug>
#include "root.h"
#include "spline.h"
#include <QPainter>
#include <QMetaObject>
#include "Attributes/stringattribute.h"
#include <QModelIndex>
#include "scene.h"


INIT_CREATOR_MAP(Object);

Object::Object(Object *parent) : QObject(parent)
{
    addAttribute("TransformationAttribute", new TransformationAttribute());
    addAttribute("NameAttribute", new StringAttribute("Name:", genericName()));
}

void Object::deserialize(QDataStream &stream)
{
    stream >> _id;


    qDeleteAll(_attributes);
    stream >> _attributes;
    for (Attribute* a : _attributes) {
        a->setObject(this);
        connect(a, SIGNAL(changed()), this, SIGNAL(changed()));
    }


    QList<Object*> children;
    stream >> children;
    for (Object* o : children) {
        o->_deserialize_mode = true;
        o->setParent(this);
        o->_deserialize_mode = false;
    }
}

void Object::serialize(QDataStream &stream) const
{
    stream << id();
    stream << _attributes;
    stream << children();
}

Object::~Object()
{
    qDeleteAll(_attributes);
}

void Object::setId(quint64 id, Scene* scene)
{
    Q_ASSERT_X(!_id_set_by_user, "Object::setId", "Trying to set ID twice");
    _id_set_by_user = true;
    _id = id;
    _scene = scene;
    setName(genericName());
}

void Object::draw(QPainter &painter)
{
    painter.save();
    painter.setTransform(localTransform(), true);
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
    painter.drawLine(QPointF(0, 0), QPointF(0, 20));
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPointF(0, 0), QPointF(20, 0));
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
    QTransform gT;
    if (!_deserialize_mode) gT = globalTransform();

    if (Object::parent()) {
        disconnect(this, SIGNAL(changed()), parent, SIGNAL(changed()));
    }
    QObject::setParent(parent);
    if (Object::parent()) {
        connect(this, SIGNAL(changed()), parent, SIGNAL(changed()));
    }
    if (!_deserialize_mode) setGlobalTransform(gT);
}

void Object::addChild(Object* child, int pos)
{
    if (!child) return;
    if (pos < 0) {
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
    case 0:     return name();
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

QTransform Object::globalTransform() const
{
    if (!parent()) return localTransform();
    return localTransform() * parent()->globalTransform();
}

void Object::setGlobalTransform(QTransform t)
{
    if (!parent()) setLocalTransform(t);
    else setLocalTransform(t * parent()->globalTransform().inverted() );
}

QTransform Object::localTransform() const
{
    Attribute* attribute = attributes()["TransformationAttribute"];
    return ((TransformationAttribute*) attribute)->value();
}

void Object::setLocalTransform(QTransform t)
{
    Attribute* attribute = attributes()["TransformationAttribute"];
    return ((TransformationAttribute*) attribute)->setValue(t);
}

QString Object::name() const
{
    Attribute* attribute = attributes()["NameAttribute"];
    return ((StringAttribute*) attribute)->string();
}

void Object::setName(QString name)
{
    Attribute* attribute = attributes()["NameAttribute"];
    ((StringAttribute*) attribute)->setString(name);
}

QPointF Object::map(QPointF pos, bool translate) const
{
    QTransform trans = globalTransform().inverted();
    if (!translate)
        trans = QTransform(trans.m11(), trans.m12(), 0, trans.m21(), trans.m22(), 0, 0, 0, 1);
    return trans.map(pos);
}

template<typename T> T* Object::attribute(QString key) const
{
    return (T*) (attributes()[key]);
}

QStringList Object::attributeKeys(QString classname)
{

    auto con = [](QStringList l1, QStringList l2) {
        l1.append(l2);
        return l1;
    };

    //TODO

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
    a->setObject(this);
    _attributes.insert(key, a);
    connect(a, SIGNAL(changed()), this, SIGNAL(changed()));
}

QList<quint64> Object::idsOfAllDescendants() const
{
    QList<quint64> list;
    list << id();
    for (Object* o : children())
        list << o->idsOfAllDescendants();
    return list;
}

QList<Object*> Object::descendants()
{
    QList<Object*> list;
    list << this;
    for (Object* o : children())
        list << o->descendants();
    return list;
}

void Object::emitChanged()
{
    emit changed();
}

void Object::setSelected(bool selected)
{
    if (_isSelected == selected) return;

    _isSelected = selected;
    emit changed();
}

QDataStream& operator<<(QDataStream& stream, const Object* o)
{
    stream << QString(o->metaObject()->className());
    o->serialize(stream);
    return stream;
}

QDataStream& operator>>(QDataStream& stream, Object* &o)
{
    QString classname;
    stream >> classname;

    o = Object::createInstance(classname);
    o->deserialize(stream);

    if (!o) {
        qWarning() << "Warning: Classname " << classname << "not found.";
        Q_ASSERT_X(o, "Object::deserialize", "deserialization failed.");
    }
    return stream;
}

QModelIndex Object::index()
{
    if (!parent())
        return scene()->createIndex(0, 0, this);

    return parent()->index().child(row(), 0);
}
