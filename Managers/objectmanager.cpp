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

void ObjectManager::setScene(Scene *s)
{
    Manager::setScene(s);
    _treeView->setModel(s);
    if (s) {
        _treeView->setSelectionModel(s->selectionModel());
        connect(s->selectionModel(), &QItemSelectionModel::selectionChanged, [this](){
            _treeView->dataChanged(QModelIndex(), QModelIndex());
        });
    }
}
