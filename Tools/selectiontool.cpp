#include "selectiontool.h"
#include <QDebug>
#include "Dialogs/pointeditdialog.h"
#include "Objects/spline.h"

REGISTER_DEFN_TYPE(Tool, SelectionTool);

bool SelectionTool::_justSelectedOrRemoved = false;

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

void SelectionTool::perform_virtual(Object *o)
{
    PointObject* pointObject = (PointObject*) o;
    Point* p = pointObject->pointAt(interaction(o).point());

    if (p && interaction().click() == Interaction::DoubleClick) {
        PointEditDialog::exec_static(p,
                                     pointObject->inherits(CLASSNAME(Spline)) && ((Spline*) pointObject)->type() == Spline::Bezier,
                                     parentWidget());
    }

    if (interaction().type() == Interaction::Press) {
        if (p && !p->isSelected()) {
            _justSelectedOrRemoved = true;
        }
        if (interaction().modifiers() != Qt::SHIFT)
            pointObject->deselectAllPoints();
        if (p) {
            pointObject->selectPoint(p);
        }
    } else if (interaction().type() == Interaction::Release) {
        if (interaction().modifiers() != Qt::SHIFT) {
            pointObject->deselectAllPoints();
        }
        if (p && !p->isSelected()) {
            pointObject->selectPoint(p);
        }
        if (p && p->isSelected() && !_justSelectedOrRemoved) {
            pointObject->deselectPoint(p);
        }
        _justSelectedOrRemoved = false;
    } else if (interaction().type() == Interaction::Move) {
        for (Point* point : pointObject->selection()) {
            point->move(interaction(o).point());
        }
        if (!pointObject->selection().isEmpty()) {
            pointObject->emitChanged();
            _justSelectedOrRemoved = true;
        }
    }
}
