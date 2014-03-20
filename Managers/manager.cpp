#include "manager.h"
#include <QDebug>
#include <QMainWindow>

INIT_CREATOR_MAP(Manager);

Manager::Manager(QWidget *parent) : QDockWidget(parent)
{
}

Manager::~Manager()
{
    setScene(0);
}

void Manager::setScene(Scene *s)
{
    if (s == _scene) return;

    if (_scene) {
        _scene->removeManager(this);
    }

    _scene = s;

    if (_scene) {
        _scene->addManager(this);
    }

    selectionChanged();
    sceneChanged();
}

void Manager::closeEvent(QCloseEvent *event)
{
    QDockWidget::closeEvent(event);
    deleteLater();
}
