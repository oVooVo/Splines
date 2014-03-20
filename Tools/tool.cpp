#include "tool.h"

INIT_CREATOR_MAP(Tool);

Tool::Tool()
{
}

void Tool::config(const Interaction &interaction)
{
    _interaction = interaction;
}

void Tool::perform(Object *o)
{
    if (canPerform(o))
        _perform_(o);
}

Interaction Tool::interaction(Object *o) const
{
    if (o) {
        return _interaction.mapCopy(o->globalTransform());
    } else {
        return _interaction;
    }
}
