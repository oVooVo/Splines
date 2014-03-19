#include "newpointtool.h"
#include "Objects/object.h"
#include "Objects/pointobject.h"
#include "point.h"

REGISTER_DEFN_TYPE(Tool, NewPointTool);

NewPointTool::NewPointTool()
{
}

void NewPointTool::perform(Object *o)
{
    if (interaction().click() == Interaction::SingleClick
            && interaction().button() == Qt::LeftButton
            && interaction().type() == Interaction::Press
            && interaction().modifiers() == Qt::NoModifier
            && o->inherits(CLASSNAME(PointObject))) {

        PointObject* p = (PointObject*) o;
        p->addPoint(new Point(o->map(interaction().point())));
    }
}
