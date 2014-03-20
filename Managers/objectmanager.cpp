#include "objectmanager.h"
#include <QKeyEvent>
#include <QDebug>

REGISTER_DEFN_MANAGAERTYPE(ObjectManager);

ObjectManager::ObjectManager(QWidget *parent) :
    Manager(parent)
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
    setWidget(_treeView);
    setWindowTitle("Object Manager");
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

void ObjectManager::setScene(Scene *scene)
{
    _treeView->setModel(scene);
    if (scene)
        _treeView->setSelectionModel(scene->selectionModel());
    Manager::setScene(scene);
}
