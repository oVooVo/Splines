#include "scene.h"
#include <QDebug>

Scene::Scene()
{
    _root = new Root();
}

void Scene::addObject(Object *o)
{
    if (!_freeIds.isEmpty()) {
        o->setId(_freeIds.pop());
    }
    o->setId(_objectCounter);
    _objectCounter++;
    _objects.insert(o->id(), o);

    if (!o->parent())
        o->setParent(_root);

    QModelIndex pi = createIndex(0, 0, _root);
    beginInsertRows(pi, 0, _root->childCount());
    QModelIndex index = createIndex(o->row(), 0, o);
    setData(index, o->name(), Qt::DisplayRole);
    dataChanged(index, index);
    endInsertRows();
}

void Scene::removeObject(Object *o)
{
    if (_objects.values().contains(o))
        removeObject(_objects.key(o));
}

void Scene::removeObject(quint64 id)
{
    if (_objects.keys().contains(id)) {
        _freeIds.push(id);
        _objects.remove(id);
    }
}

void Scene::draw(QPainter &painter)
{
    if (_root) {
        _root->draw(painter);
    }
}

QVariant Scene::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    Object* o = static_cast<Object*>(index.internalPointer());
    qDebug() << "return " <<  o->data(index.column());
    return o->data(index.column());
}

Qt::ItemFlags Scene::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return 0;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant Scene::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role== Qt::DisplayRole)
        return _root->data(section);
    return QVariant();
}

QModelIndex Scene::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Object* parentObject;
    if (!parent.isValid())
        parentObject = _root;
    else
        parentObject = static_cast<Object*>(parent.internalPointer());

    Object* childObject = parentObject->child(row);
    if (childObject)
        return createIndex(row, column, childObject);
    else
        return QModelIndex();
}

QModelIndex Scene::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Object* parentObject =
            (static_cast<Object*>(index.internalPointer()))->parent();

    if (parentObject == _root)
        return QModelIndex();

    return createIndex(parentObject->row(), 0, parentObject);
}

int Scene::rowCount(const QModelIndex &parent) const
{
    Object* parentObject;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentObject = _root;
    else
        parentObject = static_cast<Object*>(parent.internalPointer());

    return parentObject->childCount();
}

int Scene::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<Object*>(parent.internalPointer())->columnCount();
    else
        return _root->columnCount();
}



















