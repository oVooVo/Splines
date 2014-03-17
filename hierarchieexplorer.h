#ifndef HIERARCHIEEXPLORER_H
#define HIERARCHIEEXPLORER_H

#include <QTreeView>
#include <scene.h>


class HierarchieExplorer : public QTreeView
{
    Q_OBJECT
public:
    explicit HierarchieExplorer(QWidget *parent = 0);
    Scene* model() const { return (Scene*) QTreeView::model(); }
    void setModel(Scene *model);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);


private:
    void deleteSelected();

};

#endif // HIERARCHIEEXPLORER_H
