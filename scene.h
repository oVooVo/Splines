#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QHash>
#include "Objects/object.h"
#include "Objects/root.h"
#include <QStack>
#include <QAbstractItemModel>
class Scene : public QAbstractItemModel
{
    Q_OBJECT
public:
    Scene();

    //------------
    // Add or remove Objects
    //------------
public:
    void addObject(Object* o);
    void removeObject(Object* o);
    void removeObject(quint64 id);
private:
    Root* _root;
    quint64 _objectCounter = 0;
    QStack<quint64> _freeIds;
    QHash<quint64, Object*> _objects;

    //------------
    // drawing
    //------------
public:
    void draw(QPainter &painter);

    //------------
    // Tree Model
    //------------
public:
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

private:


};

#endif // SCENE_H
