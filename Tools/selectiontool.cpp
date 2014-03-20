#include "selectiontool.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Tool, SelectionTool);

SelectionTool::SelectionTool()
{
}

bool SelectionTool::canPerform(const Object *o) const
{
    if (!o->inherits(CLASSNAME(PointObject))) return false;

    if (interaction().button() == Qt::LeftButton) return true;
    if (interaction().type() == Interaction::Move) return true;

    return false;
}

void SelectionTool::_perform_(Object *o)
{
    PointObject* pointObject = (PointObject*) o;
    Point* p = pointObject->pointAt(interaction(o).point());

    if (interaction().type() == Interaction::Press) {
        if (interaction().modifiers() != Qt::SHIFT) {
            pointObject->deselectAll();
        }
        if (!p) return;
        if (p->isSelected()) {
            pointObject->deselect(p);
        } else {
            pointObject->select(p);
        }
    } else if (interaction().type() == Interaction::Move) {
        for (Point* point : pointObject->selection()) {
            point->move(interaction(o).point());
        }
        if (!pointObject->selection().isEmpty())
            pointObject->emitChanged();
    }
}
