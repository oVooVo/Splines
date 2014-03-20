#include "deselectalltool.h"
#include "Objects/pointobject.h"

REGISTER_DEFN_TYPE(Tool, DeselectAllTool);


DeselectAllTool::DeselectAllTool()
{
}

void DeselectAllTool::_perform_(Object *o)
{
    PointObject* p = (PointObject*) o;
    p->deselectAll();
}

bool DeselectAllTool::canPerform(const Object *o) const
{
    return o->inherits(CLASSNAME(PointObject));
}

