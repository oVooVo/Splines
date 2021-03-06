#include "attribute.h"
#include <QDebug>
#include "Objects/object.h"
#include "scene.h"

INIT_CREATOR_MAP(Attribute);

Attribute::Attribute(QString label)
{
    _label = label;
}

QDataStream& operator<<(QDataStream& out, const Attribute* a)
{
    out << QString(a->metaObject()->className()) << a->_label;
    (const_cast<Attribute*>(a))->registerAttributeData(out, Attribute::Serialize);
    return out;
}

QDataStream& operator>>(QDataStream& in, Attribute* &a)
{
    QString classname;
    in >> classname;

    a = Attribute::createInstance(classname);
    in >> a->_label;

    if (!a) {
        qWarning() << "Warning: Classname " << classname << "not found.";
        Q_ASSERT_X(a, "Attribute::deserialize", "deserialization failed.");
    }
    a->registerAttributeData(in, Attribute::Deserialize);

    return in;
}

void Attribute::blockSnapshot(bool b)
{
    _snapshotsBlocked = b;
}

void Attribute::beforeChange()
{
    if (_snapshotsBlocked) return;

    _object->scene()->takeSnapshot();

}

