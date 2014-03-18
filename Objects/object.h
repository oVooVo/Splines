#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QTransform>
#include "Attributes/attribute.h"
#include "Attributes/transformationattribute.h"
#include <QHash>
#include <QMap>


class Object;
#define OBJECT_CREATOR_MAP_TYPE QMap<QString, Object* (*)(QDataStream&)>
template<typename T> Object *createObjectFromStream(QDataStream& stream) { return new T(stream); }

class Object : public QObject
{
    Q_OBJECT
public:

    //---------------
    // ctor, dtor
    //---------------
    /**
     * @brief Object creates new Object with given parent.
     * @param parent the parent of the new object.
     */
    Object(Object* parent = 0);

    /**
     * @brief Object creates new Object out of a QDataStream. Use this constructor only in context of serialization
     * @param stream the object is created from data of this stream
     */
    Object(QDataStream& stream);

    /**
     * @brief ~Object destructs this object, all children and all attributes.
     */
    virtual ~Object();

    /**
     * @brief initAttributes initialize Attributes. This Method defines which attributes this Object has.
     */
    virtual void initAttributes();



    //---------------
    // drawing
    //---------------
public:
    /**
     * @brief draws this Object and all its children
     * @param painter paints this objects
     */
    void draw(QPainter &painter);

public:
    /**
     * @brief localeTransform convienience functions to access locale transformation
     * @return locale Transformation (relative to this objects parent).
     */
    QTransform localeTransform() const;
    void setLocaleTransform(QTransform t);

    /**
     * @brief globaleTransform returns the globale transformation relative to the root
     * @return globaleTransform returns the globale transformation relative to the root
     */
    QTransform globaleTransform() const;
    void setGlobaleTransform(QTransform t);

protected:
    /**
     * @brief drawIndividual does the object specific painting
     * @param painter paints the object
     */
    virtual void drawIndividual(QPainter &painter);


    //---------------
    // family stuff
    //---------------
public:
    /**
     * @brief children returns Object* list instead of QObject list since all children of Object are Objects*.
     * @return Object* list instead of QObject list since all children of Object are Objects*.
     * @overload QObject::children() const
     */
    QList<Object *> children() const;

    /**
     * @brief parent returns the parent of this object as Object*
     * @return parent of this object as Object*
     * @overload QObject::parent() const
     */
    Object* parent() const;

    /**
     * @brief setParent sets the parent of this Object. Ensures that parent of this object is always Object*
     * @param parent sets the parent of this Object.
     */
    void setParent(Object *parent);

    /**
     * @brief addChild adds a child to this Object. This Object becomes automatically a parent of child.
     * @param child the new child of this Object.
     * @param pos the position where child is inserted. If pos < 0, this does exactly the same as calling setParent on child.
     */
    void addChild(Object* child, int pos = -1);

    //---------------
    // Tree item
    //---------------
public:
    Object* child(int row) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    bool insertChildren(int position, int count, int columns);
    bool removeChildren(int position, int count);



    //---------------
    // basic attributes
    //---------------
public:
    void setId(quint64 id);
    quint64 id() const { return _id; }
private:
    quint64 _id = 0;

public:
    QString name() const { return _name; }
    void setName(QString name) { _name = name; }
private:
    QString _name = "";
protected:
    QString genericName() const;

    //------------------
    // AttributeSystem
    //------------------
protected:
    void addAttribute(QString key, Attribute* a);
private:
    QHash<QString, Attribute*> _attributes;
public:
    QHash<QString, Attribute*> attributes() const { return _attributes; }
    static QStringList attributeKeys(QString classname);

    //------------------
    // serilization
    //------------------
public:
    virtual void serialize(QDataStream& stream) const;
    static Object* deserialize(QDataStream& stream);
    friend QDataStream& operator<<(QDataStream& stream, const Object* o);
    friend QDataStream& operator>>(QDataStream& stream, Object* &o);

    QPointF map(QPointF pos, bool translate = true) const;


    //------------------
    // interaction
    //------------------
    virtual void insert(QPointF globalPos);
    virtual void select(QPointF globalPos, bool extended);
    virtual void remove(QPointF globalPos);
    virtual void removeSelected() {}
    virtual void moveSelected(QPointF t);


signals:
    void changed();

protected:
    static OBJECT_CREATOR_MAP_TYPE *_creatorMap;
    static Object *createInstance(QString className, QDataStream &stream);



};

template<typename T>
struct ObjectRegister : Object
{
    ObjectRegister(QString className) : Object()
    {
        if (!_creatorMap)
            _creatorMap = new OBJECT_CREATOR_MAP_TYPE();
        _creatorMap->insert(className, &createObjectFromStream<T>);
    }
};

#define REGISTER_DECL_OBJECTTYPE(CLASSNAME) \
    static ObjectRegister<CLASSNAME> reg

#define REGISTER_DEFN_OBJECTTYPE(CLASSNAME) \
    ObjectRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

QDataStream& operator<<(QDataStream& stream, const Object* o);
QDataStream& operator>>(QDataStream& stream, Object* &o);

#endif // OBJECT_H
