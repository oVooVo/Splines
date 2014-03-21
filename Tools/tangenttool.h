#ifndef TANGENTTOOL_H
#define TANGENTTOOL_H

#include "tool.h"

class TangentTool : public Tool
{
    Q_OBJECT
public:
    TangentTool();

    bool isCommand() const { return false; }

protected:
    bool canPerform(const Object* o) const;
    void perform_virtual(Object*);


    REGISTER_DECL_TYPE(Tool, TangentTool);
};

#endif // TANGENTTOOL_H
