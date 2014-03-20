#include "selectalltool.h"
#include "Objects/pointobject.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Tool, SelectAllTool);

SelectAllTool::SelectAllTool()
{
}

void SelectAllTool::_perform_(Object *o)
{
    PointObject* p = (PointObject*) o;
    p->selectAll();
}

bool SelectAllTool::canPerform(const Object *o) const
{
    return o->inherits(CLASSNAME(PointObject));
}
