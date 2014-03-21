#include "tangenttool.h"
#include "Objects/spline.h"
#include <QDebug>
#include "Dialogs/pointeditdialog.h"

REGISTER_DEFN_TYPE(Tool, TangentTool);

Point* TangentTool::_currentPoint = 0;

TangentTool::TangentTool()
{
}

bool TangentTool::canPerform(const Object *o) const
{
    if (!o->inherits(CLASSNAME(Spline))) return false;
    if (((Spline*) o)->type() != Spline::Bezier) return false;

    if (interaction().button() == Qt::LeftButton) return true;
    if (interaction().type()   == Interaction::Move) return true;

    return false;
}

void TangentTool::reset()
{
    if (_currentPoint) {
        _currentPoint->selectTangent(Point::NoTangent);
    }
    _currentPoint = 0;
}

void TangentTool::perform_virtual(Object *o)
{
    Spline* spline = (Spline*) o;

    if (interaction().click() == Interaction::DoubleClick) {
        Point* p = spline->pointAt(interaction(o).point());
        if (!p) return;

        PointEditDialog::exec_static(p, spline->type() == Spline::Bezier,
                              parentWidget());

        return;
    }

    switch (interaction().type()) {
    case Interaction::Press:
        _currentPoint = spline->selectTangentAt(interaction(o).point());
        if (!_currentPoint) return;

        break;
    case Interaction::Release:
        reset();
        break;
    case Interaction::Move:
        if (_currentPoint) {
            _currentPoint->moveTangent(interaction(o).point(),
                                       (interaction().modifiers() & Qt::SHIFT) ?
                                           Point::Single : Point::Simultan
                                       );
            spline->emitChanged();
        }
    case Interaction::Invalid:
    default:
        break;
    }

}
