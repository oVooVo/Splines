#include "selectiontool.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Tool, SelectionTool);

SelectionTool::SelectionTool()
{
}

bool SelectionTool::canPerform(const Object *o) const
{
    return interaction().button() == Qt::LeftButton
            && interaction().type() == Interaction::Press
            && o->inherits(CLASSNAME(PointObject));
}

void SelectionTool::_perform_(Object *o)
{
    PointObject* pointObject = (PointObject*) o;
    Point* p = pointObject->pointAt(interaction().point());


    if (interaction().modifiers() != Qt::SHIFT) {
        pointObject->deselectAll();
    }

    if (!p) return;
    if (p->isSelected()) {
        pointObject->deselect(p);
    } else {
        pointObject->select(p);
    }
}
