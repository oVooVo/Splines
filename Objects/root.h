#ifndef ROOT_H
#define ROOT_H

#include "object.h"

class Root : public Object
{
    Q_OBJECT
public:
    Root(Root* parent = 0);

    void drawIndividual(QPainter &painter);

private:
    REGISTER_DECL_OBJECTTYPE(Root);
};

#endif // ROOT_H
