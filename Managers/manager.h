#ifndef MANAGER_H
#define MANAGER_H

#include "scene.h"


class Manager
{
public:
    Manager();
    virtual ~Manager() {}

    Scene* scene() const { return _scene; }
    virtual void setScene(Scene* s);
    virtual void selectionChanged() {}
    virtual void sceneChanged() {}

private:
    Scene* _scene = 0;

};

#endif // MANAGER_H
