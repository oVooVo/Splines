#ifndef DESELECTALLTOOL_H
#define DESELECTALLTOOL_H

#include "tool.h"

class DeselectAllTool : public Tool
{
public:
    DeselectAllTool();
    QString actionText() const { return tr("Deselect all points"); }
    bool isCommand() const { return true; }


protected:
    void perform_virtual(Object *o);
    bool canPerform(const Object *o) const;

    REGISTER_DECL_TYPE(Tool, DeselectAllTool);
};

#endif // DESELECTALLTOOL_H
