#include "tool.h"

INIT_CREATOR_MAP(Tool);

Tool::Tool()
{
}

void Tool::config(const Interaction &interaction)
{
    _interaction = interaction;
}

bool Tool::perform(Object *o)
{
    if (canPerform(o)) {
        perform_virtual(o);
        return true;
    }
    return false;
}

Interaction Tool::interaction(Object *o) const
{
    if (o) {
        return _interaction.mapCopy(o->globalTransform().inverted());
    } else {
        return _interaction;
    }
}
