#ifndef TANGENTTOOL_H
#define TANGENTTOOL_H

#include "tool.h"
#include "Objects/spline.h"

class TangentTool : public Tool
{
    Q_OBJECT
public:
    TangentTool();

    bool isCommand() const { return false; }

protected:
    bool canPerform(const Object* o) const;
    void perform_virtual(Object*);

private:
    static Point* _currentPoint;
    static Point::Tangent _currentTangent;
    void reset();


    REGISTER_DECL_TYPE(Tool, TangentTool);
};

#endif // TANGENTTOOL_H
