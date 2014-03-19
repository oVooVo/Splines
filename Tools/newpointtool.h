#ifndef NEWPOINTTOOL_H
#define NEWPOINTTOOL_H

#include "tool.h"

#define CLASSNAME(T) T::staticMetaObject.className()

class NewPointTool : public Tool
{
public:
    NewPointTool();
    void perform(Object *o);

private:
    QPointF _pos;

};

#endif // NEWPOINTTOOL_H
