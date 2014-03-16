#ifndef ROOT_H
#define ROOT_H

#include "object.h"

class Root : public Object
{
    Q_OBJECT
public:
    Root(Root* parent = 0);
    Root(QDataStream& stream);

public:
    void serialize(QDataStream& stream) const;
};

#endif // ROOT_H
