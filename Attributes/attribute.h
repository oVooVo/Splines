#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QObject>
#include <QDataStream>

class Attribute : public QObject
{
    Q_OBJECT
public:
    Attribute();
    Attribute(QDataStream& stream) { Q_UNUSED(stream); }
    virtual void serialize(QDataStream& out) const;
    static Attribute* deserialize(QDataStream& in);
};

QDataStream& operator<<(QDataStream& out, const Attribute* a);
QDataStream& operator>>(QDataStream& in,  Attribute* &a);

#endif // ATTRIBUTE_H
