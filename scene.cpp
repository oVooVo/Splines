#include "scene.h"
#include <QDebug>
#include "Objects/spline.h"
#include <QStringList>
#include <QMimeData>
#include "Tools/newpointtool.h"

QList<QModelIndex> Scene::_draggedObjects;

Scene::Scene(Root *root)
{
    _root = root;
    connect(_root, SIGNAL(changed()), this, SIGNAL(changed()));
    _selectionModel = new QItemSelectionModel(this);

    _tool = new NewPointTool();
}

Scene::~Scene()
{
    delete _root;
}

void Scene::addObject(Object *o)
{
    o->setId(requestId());
    _objects.insert(o->id(), o);
    beginInsertRows(QModelIndex(), _root->childCount(), _root->childCount());
    o->setParent(_root);
    endInsertRows();
    emit changed();
}

void Scene::removeObject(QModelIndex index)
{
    Q_ASSERT_X(index.isValid(), "Scene::removeObject", "Trying to delete root or indexless object");
    Object* o = getObject(index);
    beginRemoveRows(index.parent(), o->row(), o->row());

    for (quint64 id : o->idsOfAllDescendants())
        _freeIds.enqueue(id);
    delete o;
    endRemoveRows();
    emit changed();
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

    for (Object* o : objects) {
        parentObject->addChild(o, position);
        connect(o, SIGNAL(changed()), this, SIGNAL(changed()));
    }
    beginInsertRows(parent, position, position + objects.size() - 1);
    endInsertRows();
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

    QList<Object*> objects;

    _draggedObjects.clear();
    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            objects << getObject(index);
            _draggedObjects << index;
        }
    }

    stream << objects;

    mimeData->setData("application/Object", encodedData);
    return mimeData;
}


bool Scene::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (action != Qt::MoveAction && action != Qt::CopyAction)
        return false;

    if (!data->hasFormat("application/Object"))
        return false;

    if (column > 0)
        return false;


    QList<Object*> dropped;
    QByteArray encodedObject = data->data("application/Object");
    QDataStream stream(&encodedObject, QIODevice::ReadOnly);
    stream >> dropped;
    for (Object* o : dropped) {
        if (action == Qt::CopyAction) {
            o->setId(requestId());
        }
        insertRow(row, parent, o);
    }
    if (action == Qt::MoveAction) {
        for (QModelIndex i : _draggedObjects)
            removeObject(i);
    }
    for (Object* o : dropped) {
        _freeIds.removeOne(o->id());
    }
    emit changed();
    return false;
}

quint64 Scene::requestId()
{
    if (_freeIds.isEmpty()) {
        return _objectCounter++;
    } else {
        return _freeIds.dequeue();
    }
}

QList<Object*> Scene::selectedObjects() const
{
    QList<Object*> list;
    for (QModelIndex index : selectionModel()->selection().indexes())
        list << getObject(index);
    return list;
}

void Scene::processInteraction(Interaction &interaction)
{
    if (!_tool) return;

    _tool->config(interaction);
    for (Object* o : selectedObjects()) {
        _tool->perform(o);
    }

}


QDataStream& operator<<(QDataStream& out, const Scene* s)
{
    s->_root->serialize(out);
    out << s->_freeIds << s->_objectCounter;
    return out;
}

QDataStream& operator>>(QDataStream& in, Scene* &s)
{
    Object* root = Object::deserialize(in);
    Q_ASSERT_X(QString(root->metaObject()->className()) == "Root", "Scene operator>>", "root is not of type Root");
    s = new Scene((Root*) root);
    in >> s->_freeIds >> s->_objectCounter;
    return in;
}



