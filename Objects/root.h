#ifndef ROOT_H
#define ROOT_H

#include "object.h"

class Root : public Object
{
    Q_OBJECT
public:
    Root(Root* parent = 0);

    void drawIndividual(QPainter &painter);

    bool makeAction() const { return false; }

private:
    REGISTER_DECL_TYPE(Object, Root);
};

#endif // ROOT_H
