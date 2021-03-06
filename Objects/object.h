#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QTransform>
#include "Attributes/attribute.h"
#include "Attributes/transformationattribute.h"
#include <QHash>
#include <QMap>
#include "interaction.h"
#include "action.h"
#include "register_defines.h"

class Scene;
class Object : public QObject, public Action
{
    Q_OBJECT
    DECL_MEMBER(Object)

public:

    //------------------------------
    //
    // ctor, dtor
    //
    //------------------------------
    /**
     * @brief Object creates new Object with given parent.
     * @param parent the parent of the new object.
     */
    Object(Object* parent = 0);


    /**
     * @brief ~Object destructs this object, all children and all attributes.
     */
    virtual ~Object();



    //------------------------------
    //
    // drawing
    //
    //------------------------------
public:
    /**
     * @brief draws this Object and all its children
     * @param painter paints this objects
     */
    void draw(QPainter &painter);

protected:
    /**
     * @brief drawIndividual does the object specific painting
     * @param painter paints the object
     */
    virtual void drawIndividual(QPainter &painter);




    //------------------------------
    //
    // transformation
    //
    //------------------------------
public:
    /**
     * @brief localTransform convienience functions to access local transformation
     * @return local Transformation (relative to this objects parent).
     */
    QTransform localTransform() const;

    /**
     * @brief setLocalTransform sets the local transformation
     * @param t is the new local transformation
     */
    void setLocalTransform(QTransform t);

    /**
     * @brief globalTransform returns the global transformation relative to the root
     * @return globalTransform returns the global transformation relative to the root
     */
    QTransform globalTransform() const;

    /**
     * @brief setGlobalTransform sets the global transformation
     * @param t the new global transformation
     */
    void setGlobalTransform(QTransform t);




    //------------------------------
    //
    // family stuff
    // manly overriden functions from QObject that return or take Object* instead QObject*
    //------------------------------
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
     * @see QAbstractItemModel
     */
    void addChild(Object* child, int pos = -1);

    /**
     * @brief child returns the rows-th child of this.
     * @param row the index of the child returned
     * @return the rows-th child or zero if row < 0 or row > childCount
     * @see QAbstractItemModel
     */
    Object* child(int row) const;

    /**
     * @brief childCount returns the number of children
     * @return the number of children
     * @see QAbstractItemModel
     */
    int childCount() const;

    /**
     * @brief columnCount the number of columns (requiert to implement Scene accordingly)
     * @return returns always 1
     * @see QAbstractItemModel
     */
    int columnCount() const;

    /**
     * @brief data returns the "thing" that is displayed in TreeView in given column
     * @param column the column where the Variant is displayed
     * @return the Variant that is displayed in column 1
     * @see QAbstractItemModel
     */
    QVariant data(int column) const;

    /**
     * @brief row returns i when this is the i-th child of its parent.
     * @return i when this is the i-th child of its parent.
     * @see QAbstractItemModel
     */
    int row() const;

    /**
     * @brief removeChildren returns count children from position to position + count - 1
     * @param position the index of the first child that is deleted
     * @param count the number of deleted children
     * @return
     */
    bool removeChildren(int position, int count);



    //------------------------------
    //
    // id
    //
    //------------------------------

public:
    /**
     * @brief setId sets the id of this object. The id can only be set once!
     * @param id the new id of this object.
     */
    void setId(quint64 id, Scene *scene);

    /**
     * @brief id returns the id of this object.
     * @return the id of this object.
     */
    quint64 id() const { return _id; }

    /**
     * @brief idsOfAllDescendants returns a list of ids of all descendants.
     * @return a list of ids of all descendants
     */
    QList<quint64> idsOfAllDescendants() const;
    QList<Object*> descendants();

private:
    /**
     * @brief _id the id of this object
     */

    quint64 _id = 0;
    /**
     * @brief _id_set_by_user true if the id was set by user, false otherwise.
     */
    bool _id_set_by_user = false;


public:
    QString name() const;
    void setName(QString name);
protected:
    QString genericName() const;

    //------------------------------
    //
    // AttributeSystem
    //
    //------------------------------
protected:
    /**
     * @brief addAttribute adds a given attribute to this object. Please use this method only in (overloaded) initializeAttributes()!
     * @param key the name of the attribute
     * @param a the attribute
     */
    void addAttribute(QString key, Attribute* a);

private:
    /**
     * @brief _attributes stores the attributes
     */
    QHash<QString, Attribute*> _attributes;

public:
    /**
     * @brief attributes returns the attributes
     * @return the attributes
     */
    QHash<QString, Attribute*> attributes() const { return _attributes; }

    static QStringList attributeKeys(QString classname);
    template<typename T> T* attribute(QString key) const;




    //------------------------------
    //
    // serialization
    //
    //------------------------------
public:
    virtual void serialize(QDataStream& stream) const;
    virtual void deserialize(QDataStream& stream);
    friend QDataStream& operator<<(QDataStream& stream, const Object* o);
    friend QDataStream& operator>>(QDataStream& stream, Object* &o);
private:
    /**
     * @brief _deserialize_mode switch that indicates deserialization mode. Some methods work different in this mode,
     *  so setParent will not try to keep globaleTransform.
     */
    bool _deserialize_mode = false;



    //------------------------------
    //
    // ???
    //
    //------------------------------
public:
    QPointF map(QPointF pos, bool translate = true) const;



    //------------------------------
    //
    // To generate menu entries that create a new object on click
    //
    //------------------------------
public:
    virtual QString actionText() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }
    bool isCommand() const { return true; }    // the "new Object Tool" is a command


    //-------------------------------
    //
    // keep track of own selection
    //
    //--------------------------------
public:
    void setSelected(bool selected);
    void select() { setSelected(true); }
    void deselect() { setSelected(false); }
    bool isSelected() const { return _isSelected; }
private:
    bool _isSelected = false;

    //----------------------------------
    //
    // Indexes
    //
    //------------------------
public:
    QModelIndex index();


public:
    Scene* scene() const { return _scene; }
    void setScene(Scene* s) { _scene = s; }
private:
    Scene* _scene;


signals:
    void changed();
public:
    void emitChanged();
};

REGISTERER(Object)

QDataStream& operator<<(QDataStream& stream, const Object* o);
QDataStream& operator>>(QDataStream& stream, Object* &o);

#endif // OBJECT_H
