#include "deletepointtool.h"
#include "Objects/pointobject.h"

REGISTER_DEFN_TYPE(Tool, DeletePointTool);


DeletePointTool::DeletePointTool()
{
}

void DeletePointTool::perform_virtual(Object *o)
{
    PointObject* p = (PointObject*) o;
    p->deleteSelectedPoints();
}

bool DeletePointTool::canPerform(const Object *o) const
{
    return o->inherits(CLASSNAME(PointObject));
}

