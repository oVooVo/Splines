#ifndef HIERARCHIEEXPLORER_H
#define HIERARCHIEEXPLORER_H

#include <QTreeView>
#include <scene.h>
#include "dockablemanager.h"


class ObjectManager : public DockableManager
{
    Q_OBJECT
public:
    explicit ObjectManager(QWidget *parent = 0);
    Scene* model() const { return (Scene*) _treeView->model(); }
    void setScene(Scene *scene);

    void selectionChanged();
    void sceneChanged();

public slots:
    void restoreCollapseExpandedState();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void deleteSelected();
    QTreeView* _treeView;
    REGISTER_DECL_DOCKABLEMANAGERTYPE(ObjectManager);

private slots:
    void itemCollapsed(QModelIndex index);
    void itemExpanded(QModelIndex index);

private:
    QMap<quint64, bool> _expandedMap;

};

#endif // HIERARCHIEEXPLORER_H
