#ifndef TANGENTTOOL_H
#define TANGENTTOOL_H

#include "tool.h"

class TangentTool : public Tool
{
public:
    TangentTool();

    bool isCommand() const { return false; }

protected:
    bool canPerform(const Object* ) const { return false; }
    void _perform_(Object*) {}


    REGISTER_DECL_TYPE(Tool, TangentTool);
};

#endif // TANGENTTOOL_H
