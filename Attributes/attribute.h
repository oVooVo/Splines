#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QObject>
#include <QDataStream>
#include <QMap>


class Attribute;
// convienience define to save typing the type often
#define ATTRIBUTE_CREATOR_MAP_TYPE QMap<QString, Attribute* (*)(QDataStream&)>

//creates a new Attribute of Type T out of a given Stream.
template<typename T> Attribute *createAttributeFromStream(QDataStream& stream) { return new T(stream); }


class Attribute : public QObject
{
    Q_OBJECT
public:
    Attribute();
    Attribute(QDataStream& stream);
    virtual void serialize(QDataStream& out) const;
    static Attribute* deserialize(QDataStream& stream);
protected:
    virtual void makeConnects() {}
    void polish();

signals:
    void changed();

protected:
    static ATTRIBUTE_CREATOR_MAP_TYPE *_creatorMap;
    static Attribute *createInstance(QString className, QDataStream &stream);
};

template<typename T>
struct AttributeRegister : Attribute
{
    AttributeRegister(QString className) : Attribute()
    {
        if (!_creatorMap)
            _creatorMap = new ATTRIBUTE_CREATOR_MAP_TYPE();
        _creatorMap->insert(className, &createAttributeFromStream<T>);
    }
};

#define REGISTER_DECL_ATTRIBUTETYPE(CLASSNAME) \
    static AttributeRegister<CLASSNAME> reg

#define REGISTER_DEFN_ATTRIBUTETYPE(CLASSNAME) \
    AttributeRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

QDataStream& operator<<(QDataStream& out, const Attribute* a);
QDataStream& operator>>(QDataStream& in,  Attribute* &a);

#endif // ATTRIBUTE_H
