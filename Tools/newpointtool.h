#ifndef NEWPOINTTOOL_H
#define NEWPOINTTOOL_H

#include "tool.h"

class NewPointTool : public Tool
{
    Q_OBJECT
public:
    NewPointTool();
    bool isCommand() const { return false; }
    QString actionText() const { return tr("Add Point"); }

protected:
    void _perform_(Object *o);
    bool canPerform(const Object *o) const;

private:
    QPointF _pos;

    REGISTER_DECL_TYPE(Tool, NewPointTool);
};

#endif // NEWPOINTTOOL_H
