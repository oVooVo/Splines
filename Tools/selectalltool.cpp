#include "selectalltool.h"
#include "Objects/pointobject.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Tool, SelectAllTool);

SelectAllTool::SelectAllTool()
{
}

void SelectAllTool::perform_virtual(Object *o)
{
    PointObject* p = (PointObject*) o;
    p->selectAllPoints();
}

bool SelectAllTool::canPerform(const Object *o) const
{
    return o->inherits(CLASSNAME(PointObject));
}
