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
protected:
    virtual void serialize(QDataStream& out) const;
    static Attribute* deserialize(QDataStream& stream);
    virtual void makeConnects() {}
    void polish();

signals:
    void changed();

protected:
    static ATTRIBUTE_CREATOR_MAP_TYPE *_creatorMap;
    static Attribute *createInstance(QString className, QDataStream &stream);

    friend QDataStream& operator<<(QDataStream& out, const Attribute* a);
    friend QDataStream& operator>>(QDataStream& in,  Attribute* &a);
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
