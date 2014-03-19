#include "manager.h"

INIT_CREATOR_MAP(Manager);

Manager::Manager(QWidget *parent) : QDockWidget(parent)
{
}

void Manager::setScene(Scene *s)
{
    if (_scene) {
        disconnect(_scene, 0, this, 0);
    }
    _scene = s;
}
