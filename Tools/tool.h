#ifndef TOOL_H
#define TOOL_H

#include "Objects/object.h"
#include "interaction.h"

class Tool
{
public:
    Tool();

    virtual void perform(Object* o) = 0;
    void config(Interaction& interaction);

    Interaction interaction() const { return _interaction; }

private:
    Interaction _interaction;
};

#endif // TOOL_H
