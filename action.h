#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QIcon>

class Action
{
protected:
    Action();
    virtual QString actionText() const = 0;
    virtual QString toolTip() const = 0;
    virtual QIcon icon() const = 0;
    virtual bool isCheckable() const = 0;
//make this never public, "override" this in derived class
    static QStringList types() { Q_ASSERT(false); }

};

#endif // ACTION_H
