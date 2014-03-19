#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H

#include "tool.h"

class SelectionTool : public Tool
{
    Q_OBJECT
public:
    SelectionTool();
    void perform(Object *o);

private:
    REGISTER_DECL_TOOLTYPE(SelectionTool);
};

#endif // SELECTIONTOOL_H
