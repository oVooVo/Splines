#include "tangenttool.h"
#include "Objects/spline.h"
#include <QDebug>

REGISTER_DEFN_TYPE(Tool, TangentTool);

Point* TangentTool::_currentPoint = 0;

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

void TangentTool::reset()
{
    if (_currentPoint) {
        _currentPoint->selectTangent(Point::NoTangent);
    }
    _currentPoint = 0;
}

void TangentTool::perform_virtual(Object *o)
{
    PointObject* pointObject = (PointObject*) o;

    switch (interaction().type()) {
    case Interaction::Press:
        _currentPoint = pointObject->selectTangentAt(interaction(o).point());
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
            pointObject->emitChanged();
        }
    case Interaction::Invalid:
    default:
        break;
    }

}
