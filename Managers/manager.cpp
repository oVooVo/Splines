#include "manager.h"

Manager::Manager()
{
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
        selectionChanged();
        sceneChanged();
    }

}

