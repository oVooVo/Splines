#include "interaction.h"

const Interaction Interaction::NoInteraction = Interaction();

Interaction::Interaction(Qt::MouseButton button, QPointF pos, Click click, Qt::KeyboardModifiers modifiers)
{
    _button = button;
    _click = click;
    _modifiers = modifiers;
    _point = pos;
    _type = Press;
}

Interaction::Interaction(QPointF t, Qt::KeyboardModifiers modifiers)
{
    _point = t;
    _modifiers = modifiers;
    _type = Move;
}

Interaction::Interaction(Qt::MouseButton button, QPointF pos, Qt::KeyboardModifiers modifiers)
{
    _point = pos;
    _button = button;
    _modifiers = modifiers;
    _type = Release;
}

Interaction::Interaction(Qt::MouseButton button, Click click, Qt::KeyboardModifiers modifiers, QPointF q, Type type)
{
    _button = button;
    _point = q;
    _click = click;
    _modifiers = modifiers;
    _type = type;
}

void Interaction::map(QTransform t)
{
    QTransform trans = (type() == Move ?
                            QTransform(t.m11(), t.m12(), 0, t.m21(), t.m22(), 0, 0, 1) :
                            t  );
    _point = trans.map(_point);
}
