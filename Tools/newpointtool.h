#ifndef NEWPOINTTOOL_H
#define NEWPOINTTOOL_H

#include "tool.h"

#define CLASSNAME(T) T::staticMetaObject.className()

class NewPointTool : public Tool
{
    Q_OBJECT
public:
    NewPointTool();
    void perform(Object *o);

private:
    QPointF _pos;
    REGISTER_DECL_TYPE(Tool, NewPointTool);

};

#endif // NEWPOINTTOOL_H
