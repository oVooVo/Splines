#include "newpointtool.h"
#include "Objects/object.h"
#include "Objects/pointobject.h"
#include "point.h"

REGISTER_DEFN_TYPE(Tool, NewPointTool);

NewPointTool::NewPointTool()
{
}

bool NewPointTool::canPerform(const Object *o) const
{
    return interaction().click() == Interaction::SingleClick
            && interaction().button() == Qt::LeftButton
            && interaction().type() == Interaction::Press
            && interaction().modifiers() == Qt::NoModifier
            && o->inherits(CLASSNAME(PointObject));
}

void NewPointTool::perform_virtual(Object *o)
{
    PointObject* p = (PointObject*) o;
    p->addPoint(new Point(o->map(interaction().point())));
}
