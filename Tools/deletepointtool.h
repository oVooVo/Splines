#ifndef DELETEPOINTTOOL_H
#define DELETEPOINTTOOL_H

#include "tool.h"

class DeletePointTool : public Tool
{
    Q_OBJECT
public:
    DeletePointTool();

    void perform_virtual(Object *o);
    bool canPerform(const Object *o) const;
    bool isCommand() const { return true; }
    QString actionText() const { return "Delete selection"; }

    REGISTER_DECL_TYPE(Tool, DeletePointTool);

};

#endif // DELETEPOINTTOOL_H
