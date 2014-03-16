#include "scene.h"
#include <QDebug>
#include "Objects/spline.h"
#include <QStringList>
#include <QMimeData>

Scene::Scene()
{
    _root = new Root();
}

Scene::~Scene()
{
    delete _root;
}

void Scene::addObject(Object *o)
{
    if (!_freeIds.isEmpty()) {
        o->setId(_freeIds.dequeue());
    } else {
        o->setId(_objectCounter++); //yes, post decrement!
    }
    _objects.insert(o->id(), o);

    beginInsertRows(QModelIndex(), _root->childCount(), _root->childCount());
    o->setParent(_root);
    endInsertRows();
}

void Scene::removeObject(QModelIndex index)
{
    Q_ASSERT_X(index.isValid(), "Scene::removeObject", "Trying to delete root or indexless object");
    Object* o = getObject(index);
    beginRemoveRows(index.parent(), o->row(), o->row());
    _freeIds.enqueue(o->id());
    delete o;
    endRemoveRows();
}

void Scene::draw(QPainter &painter)
{
    if (_root) {
        _root->draw(painter);
    }
}

Object *Scene::getObject(const QModelIndex &index) const
{
    if (index.isValid()) {
        Object* item = static_cast<Object*>(index.internalPointer());
        if (item) return item;
    }
    return _root;
}

int Scene::rowCount(const QModelIndex &parent) const
{
    Object *parentItem = getObject(parent);

    return parentItem->childCount();
}

int Scene::columnCount(const QModelIndex & /* parent */) const
{
    return _root->columnCount();
}

QModelIndex Scene::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    Object* parentItem = getObject(parent);

    Object* childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex Scene::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Object* childItem = getObject(index);
    Object* parentItem = childItem->parent();

    if (parentItem == _root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


QVariant Scene::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    Object* item = getObject(index);

    return item->data(index.column());
}

QVariant Scene::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _root->data(section);

    return QVariant();
}

bool Scene::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    Object* item = getObject(index);
    item->setName(value.toString());
    return true;
}

void Scene::insertRow(int position, const QModelIndex &parent, Object* object)
{
    QList<Object*> objects;
    objects << object;
    insertRows(position, parent, objects);
}


void Scene::insertRows(int position, const QModelIndex &parent, QList<Object*> objects)
{
    Object* parentObject = getObject(parent);

    beginInsertRows(parent, position, position + objects.size() - 1);
    endInsertRows();
    for (Object* o : objects)
        o->setParent(parentObject);
}

bool Scene::removeRows(int position, int rows, const QModelIndex &parent)
{
    Object* parentItem = getObject(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

Qt::DropActions Scene::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags Scene::flags(const QModelIndex &index) const
{
    Qt::ItemFlags def = Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractItemModel::flags(index);
    if (index.isValid()) {
        def |= Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    }
    return def;
}

QStringList Scene::mimeTypes() const
{
    QStringList types;
    types << QString("application/Object");
    return types;
}

QMimeData *Scene::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::ReadWrite);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            stream << getObject(index);
        }
    }

    mimeData->setData("application/Object", encodedData);
    return mimeData;
}

bool Scene::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    QByteArray encodedObject = data->data("application/Object");
    QDataStream stream(&encodedObject, QIODevice::ReadOnly);
    Object* dropped = 0;

    stream >> dropped;
    insertRow(row, parent, dropped);
    return true;
}









