#include "tool.h"

TOOL_CREATOR_MAP_TYPE *Tool::_creatorMap = 0;

Tool::Tool()
{
}

void Tool::config(Interaction &interaction)
{
    _interaction = interaction;
}

Tool *Tool::createInstance(QString className)
{
    if (!_creatorMap)
    {
        _creatorMap = new TOOL_CREATOR_MAP_TYPE();
    }

    TOOL_CREATOR_MAP_TYPE::iterator it = _creatorMap->find(className);
    if (it == _creatorMap->end())
        return 0;
    return (it.value())();
}
