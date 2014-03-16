#ifndef ROOT_H
#define ROOT_H

#include "object.h"

class Root : public Object
{
    Q_OBJECT
public:
    Root();
    Root(QDataStream& stream);
};

#endif // ROOT_H
