#include "interaction.h"
#include <QDebug>

const Interaction Interaction::NoInteraction = Interaction();

Interaction::Interaction(Qt::MouseButton button, QPointF pos, Type type, Click click, Qt::KeyboardModifiers modifiers)
{
    _button = button;
    _point = pos;
    _type = type;
    Q_ASSERT(type != Move);
    _click = click;
    _modifiers = modifiers;
}

Interaction::Interaction(QPointF t, Qt::KeyboardModifiers modifiers)
{
    _button = Qt::NoButton;
    _point = t;
    _type = Move;
    _click = NoClick;
    _modifiers = modifiers;
}

Interaction Interaction::mapCopy(QTransform t) const
{
    Interaction m = (*this);
    m.map(t);
    return m;
}

void Interaction::map(QTransform t)
{
    QTransform trans = (type() == Move ?
                            QTransform(t.m11(), t.m12(), 0, t.m21(), t.m22(), 0, 0, 0, 1) :
                            t  );
    _point = trans.map(_point);
}
