#include "objectmanager.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

REGISTER_DEFN_DOCKABLEMANAGERTYPE(ObjectManager);

ObjectManager::ObjectManager(QWidget *parent) :
    DockableManager(parent)
{
    _treeView = new QTreeView(this);

    _treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
    _treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    _treeView->setExpandsOnDoubleClick(true);
    _treeView->setRootIsDecorated(true);
    _treeView->setHeaderHidden(true);

    _treeView->setDefaultDropAction(Qt::MoveAction);
    _treeView->setDragEnabled(true);
    _treeView->setAcceptDrops(true);
    _treeView->setDropIndicatorShown(true);

    _treeView->setAutoExpandDelay(1000);
    setWidget(_treeView);
    setWindowTitle("Object Manager");
    connect(_treeView, SIGNAL(expanded(QModelIndex)), this, SLOT(itemExpanded(QModelIndex)));
    connect(_treeView, SIGNAL(collapsed(QModelIndex)), this, SLOT(itemCollapsed(QModelIndex)));
}

void ObjectManager::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777223) { //delete
        deleteSelected();
    }
}

void ObjectManager::deleteSelected()
{
    for (QModelIndex index : model()->selectionModel()->selectedIndexes()) {
        model()->removeObject(index);
    }
}

void ObjectManager::selectionChanged()
{
    if (scene()) {
        _treeView->dataChanged(QModelIndex(), QModelIndex());
    }
}

void ObjectManager::sceneChanged()
{
    restoreCollapseExpandedState();
}

void ObjectManager::setScene(Scene *scene)
{
    _treeView->setModel(scene);
    if (scene)
        _treeView->setSelectionModel(scene->selectionModel());

    restoreCollapseExpandedState();

    Manager::setScene(scene);
}

void ObjectManager::itemCollapsed(QModelIndex index)
{
    _expandedMap.insert(scene()->object(index)->id(), false);
}

void ObjectManager::itemExpanded(QModelIndex index)
{
    _expandedMap.insert(scene()->object(index)->id(), true);
}

void ObjectManager::restoreCollapseExpandedState()
{
    // items are expanded by default
    _treeView->blockSignals(true);  // do not emit signal when expanded because this would override status in _expandedMap.
    _treeView->expandAll();
    _treeView->blockSignals(false);

    for (quint64 id : _expandedMap.keys()) {
        Object* object = scene()->object(id);
        if (!object) return;

        QModelIndex index = scene()->index(object);
        if (_expandedMap[id]) {
            _treeView->expand(index);
        } else {
            _treeView->collapse(index);
        }
    }
}
