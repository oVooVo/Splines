#include "manager.h"

MANAGER_CREATOR_MAP_TYPE *Manager::_creatorMap = 0;

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

Manager *Manager::createInstance(QString className, QWidget* parent)
{
    if (!_creatorMap)
    {
        _creatorMap = new MANAGER_CREATOR_MAP_TYPE();
    }

    MANAGER_CREATOR_MAP_TYPE::iterator it = _creatorMap->find(className);
    if (it == _creatorMap->end())
        return 0;
    return (it.value())(parent);
}
