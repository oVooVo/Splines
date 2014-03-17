#include "hierarchieexplorer.h"
#include <QKeyEvent>
#include <QDebug>

HierarchieExplorer::HierarchieExplorer(QWidget *parent) :
    QTreeView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setExpandsOnDoubleClick(true);

    setDefaultDropAction(Qt::MoveAction);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void HierarchieExplorer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777223) { //delete
        deleteSelected();
    }
}

void HierarchieExplorer::deleteSelected()
{
    for (QModelIndex index : selectionModel()->selectedIndexes()) {
        model()->removeObject(index);
    }
}

void HierarchieExplorer::mousePressEvent(QMouseEvent *event)
{
    qDebug() << model()->getObject(indexAt(event->pos()))->name();
    QTreeView::mousePressEvent(event);
}

void HierarchieExplorer::setModel(Scene *model)
{
    QTreeView::setModel(model);
    if (model) {
        setSelectionModel(model->selectionModel());
    }
}
