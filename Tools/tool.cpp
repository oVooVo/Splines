#include "tool.h"

INIT_CREATOR_MAP(Tool);

Tool::Tool()
{
}

void Tool::config(Interaction &interaction)
{
    _interaction = interaction;
}
