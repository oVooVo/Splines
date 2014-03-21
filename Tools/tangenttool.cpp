#include "tangenttool.h"
#include "Objects/spline.h"

REGISTER_DEFN_TYPE(Tool, TangentTool);

TangentTool::TangentTool()
{
}

bool TangentTool::canPerform(const Object *o) const
{
    if (!o->inherits(CLASSNAME(Spline))) return false;

    if (interaction().button() == Qt::LeftButton) return true;
    if (interaction().type()   == Interaction::Move) return true;

    return false;
}

void TangentTool::perform_virtual(Object *o)
{

}
