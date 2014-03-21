#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H

#include "tool.h"
#include "Objects/pointobject.h"

class SelectionTool : public Tool
{
    Q_OBJECT
public:
    SelectionTool();
    QString actionText() const { return tr("Select"); }
    bool isCommand() const { return false; }

protected:
    bool canPerform(const Object *o) const;
    void perform_virtual(Object *o);

    REGISTER_DECL_TYPE(Tool, SelectionTool);

private:
    static bool _justSelectedOrRemoved;
};

#endif // SELECTIONTOOL_H
