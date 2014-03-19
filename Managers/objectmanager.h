#ifndef HIERARCHIEEXPLORER_H
#define HIERARCHIEEXPLORER_H

#include <QTreeView>
#include <scene.h>
#include "manager.h"


class ObjectManager : public Manager
{
    Q_OBJECT
public:
    explicit ObjectManager(QWidget *parent = 0);
    Scene* model() const { return (Scene*) _treeView->model(); }
    void setScene(Scene *scene);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void deleteSelected();
    QTreeView* _treeView;
    REGISTER_DECL_MANAGAERTYPE(ObjectManager);

};

#endif // HIERARCHIEEXPLORER_H
