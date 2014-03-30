#include "scene.h"
#include <QDebug>
#include "Objects/spline.h"
#include <QStringList>
#include <QMimeData>
#include "Tools/newpointtool.h"
#include "Managers/manager.h"
#include "Managers/dockablemanager.h"
#include "undohandler.h"

QList<QModelIndex> Scene::_draggedObjects;

Scene::Scene(Root *root)
{
    _root = root;
    connect(_root, SIGNAL(changed()), this, SIGNAL(changed()));
    _selectionModel = new QItemSelectionModel(this);
    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(on_selectionChanged()));
    connect(this, SIGNAL(changed()), this, SLOT(on_sceneChanged()));
}

Scene::~Scene()
{
    delete _root;
}

void Scene::addObject(Object *o)
{
    takeSnapshot();

    attachId(o);
    beginInsertRows(QModelIndex(), _root->childCount(), _root->childCount());
    o->setParent(_root);
    endInsertRows();
    emit changed();
}

void Scene::removeObject(QModelIndex index)
{
    Q_ASSERT_X(index.isValid(), "Scene::removeObject", "Trying to delete root or indexless object");
    Object* o = getObject(index);
    if (!o) return;

    takeSnapshot();

    beginRemoveRows(index.parent(), o->row(), o->row());
    _objects.remove(o->id());
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
    if (action == Qt::MoveAction) {
        for (QModelIndex i : _draggedObjects)
            removeObject(i);
    }
    for (Object* o : dropped) {
        if (action == Qt::CopyAction) {
            attachId(o);
        } else {
            for (Object* desc : o->descendants()) {
                _objects.insert(desc->id(), desc);
            }
        }
        insertRow(row, parent, o);
    }

    emit changed();
    return false;
}

void Scene::attachId(Object* o)
{
    Q_ASSERT(_objectCounter < std::numeric_limits<quint64>::max());

    o->setId(_objectCounter, this);
    _objects.insert(o->id(), o);
    _objectCounter++;
}

QList<Object*> Scene::selectedObjects()
{
    if (!_selectionUpToDate) {
        _selection = selectedObjectsConst();
        _selectionUpToDate = true;
    }
    return _selection;
}

QList<Object*> Scene::selectedObjectsConst() const
{
    QList<Object*> selection;
    for (QModelIndex index : selectionModel()->selection().indexes()) {
        Object* o = getObject(index);
        o->select();
        selection << o;
    }
    return selection;
}

void Scene::processInteraction(const Interaction &interaction)
{
    if (!_tool) return;

    _tool->config(interaction); // can be configured without caring about snapshots since tool's status isnt serialized in snapshot of scene.

    bool anythingPerformed = false;
    for (Object* o : selectedObjects()) {
        anythingPerformed |= _tool->canPerform(o);
    }

    if (anythingPerformed && interaction.type() == Interaction::Press) {
        takeSnapshot();
    }

    for (Object* o : selectedObjects()) {
        _tool->perform(o);
    }
}

void Scene::setTool(Tool *tool)
{
    if (!tool->isCommand()) {
        // if tool is a tool that can be choosen and performed iteractively
        if (_tool)
            delete _tool;
        _tool = tool;
    } else {
        // if tool is a command that is performed only once
        Tool* oldTool = _tool;
        _tool = tool;
        processInteraction(Interaction::NoInteraction);
        delete _tool;
        _tool = oldTool;
    }
}

QString magic()
{
    return "OYOLO";
}

quint64 version()
{
    return 1000;
}

void Scene::serializeHeader(QDataStream &out)
{
    out << magic();
    out << (quint64) 1000; //version
}

bool Scene::deserializeHeader(QDataStream &in)
{
    QString m;
    in >> m;
    if (m != magic()) return false;

    quint64 v;
    in >> v;
    if (v != version()) return false;

    return true;
}

QDataStream& operator<<(QDataStream& out, const Scene* s)
{
    Scene::serializeHeader(out);
    out << s->root();
    out << s->_objectCounter;
    QList<quint64> selectedIds;
    for (Object* o : s->selectedObjectsConst()) {
        selectedIds.append(o->id());
    }
    out << selectedIds;
    return out;
}

QDataStream& operator>>(QDataStream& in, Scene* &s)
{
    if (!Scene::deserializeHeader(in)) {
        qWarning() << "deserializing scene failed.";
        s = 0;
    } else {
        Object* root;
        in >> root;
        Q_ASSERT_X(QString(root->metaObject()->className()) == "Root", "Scene operator>>", "root is not of type Root");
        s = new Scene((Root*) root);
        in >> s->_objectCounter;

        for (Object* o : root->descendants()) {
            s->_objects.insert(o->id(), o);
        }

        QList<quint64> selectedIds;
        in >> selectedIds;
        for (quint64 id : selectedIds) {
            s->select(id);
        }
    }
    return in;
}

void Scene::addManager(Manager *m)
{
    if (_managers.contains(m)) return;

    _managers.append(m);
}

void Scene::removeManager(Manager *m)
{
    if (!_managers.contains(m)) return;

    _managers.removeOne(m);
}

void Scene::on_sceneChanged()
{
    for (Manager* m : _managers) {
        m->sceneChanged();
    }
}

void Scene::on_selectionChanged()
{
    _selectionUpToDate = false;
    for (Manager* m : _managers) {
        m->selectionChanged();
    }
}

bool Scene::isSelected(Object *o)
{
    return selectedObjects().contains(o);
}

void Scene::takeSnapshot()
{
    _undoHandler->takeSnapshot();
}

void Scene::select(Object *o, bool s)
{
    if (!o) return;

    QItemSelectionModel::SelectionFlag flag = s ? QItemSelectionModel::Select : QItemSelectionModel::Deselect;
    if (o == root()) {
        selectionModel()->select(QModelIndex(), flag);
    } else {
        o->select();
        selectionModel()->select(index(o), flag);
    }
}

void Scene::select(quint64 id, bool s)
{
    Object* obj = _objects.value(id, 0);
    select(obj, s);
}

QModelIndex Scene::index(Object *object) const
{
    if (object == root()) return QModelIndex();

    QModelIndex ind = index(object->row(), 0, index(object->parent()));
    return ind;
}

Object* Scene::object(const QModelIndex &index) const
{
    return (Object*) index.internalPointer();
}

Object* Scene::object(const quint64 id) const
{
    return _objects.value(id, 0);
}
