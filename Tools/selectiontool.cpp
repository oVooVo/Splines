#include "selectiontool.h"

REGISTER_DEFN_TYPE(Tool, SelectionTool);

SelectionTool::SelectionTool()
{
}

bool SelectionTool::canPerform(const Object *o) const
{
    return o->inherits(CLASSNAME(PointObject));
}

void SelectionTool::_perform_(Object *o)
{
    Q_UNUSED(o);
}
