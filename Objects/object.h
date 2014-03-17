#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include "transformation.h"


class Object : public QObject
{
    Q_OBJECT
public:

    //---------------
    // ctor, dtor
    //---------------
    Object(Object* parent = 0);
    Object(QDataStream& stream);
    virtual ~Object();

    //---------------
    // drawing
    //---------------
    virtual void draw(QPainter &painter);
public:
    QTransform localeTransform() const { return _transformation; }
    QTransform globaleTransform() const;
private:
    QTransform _transformation;
signals:
    void changed();

    //---------------
    // family stuff
    //---------------
public:
    QList<Object *> children() const;
    Object* parent() const;
    void setParent(Object *parent);
    void addChild(Object* child, int pos);

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
    // serilization
    //------------------
public:
    virtual void serialize(QDataStream& stream) const;
    static Object* deserialize(QDataStream& stream);
    friend QDataStream& operator<<(QDataStream& stream, const Object* o);
    friend QDataStream& operator>>(QDataStream& stream, Object* &o);

    QPointF map(QPointF localePosition) const;


    //------------------
    // interaction
    //------------------
    virtual void insert(QPointF globalPos);
    virtual void select(QPointF globalPos, bool extended);
    virtual void remove(QPointF globalPos);
    virtual void removeSelected() {}
    virtual void moveSelected(QPointF t);


};

QDataStream& operator<<(QDataStream& stream, const Object* o);
QDataStream& operator>>(QDataStream& stream, Object* &o);

#endif // OBJECT_H
