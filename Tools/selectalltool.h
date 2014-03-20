#ifndef SELECTALLTOOL_H
#define SELECTALLTOOL_H

#include "tool.h"



class SelectAllTool : public Tool
{
    Q_OBJECT
public:
    SelectAllTool();
    QString actionText() const { return tr("Select all points"); }
    bool isCommand() const { return true; }


protected:
    void _perform_(Object *o);
    bool canPerform(const Object *o) const;

    REGISTER_DECL_TYPE(Tool, SelectAllTool);
};

#endif // SELECTALL_H
