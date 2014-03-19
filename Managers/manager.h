#ifndef MANAGER_H
#define MANAGER_H

#include <QDockWidget>
#include "scene.h"
#include <QIcon>
#include <action.h>


class Manager : public QDockWidget, public Action
{
    Q_OBJECT
    DECL_MEMBER(Manager)
public:
    Manager(QWidget* parent = 0);

public:
    Scene* scene() const { return _scene; }
    virtual void setScene(Scene* s);

    virtual QString actionText() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }
    bool isCheckable() const { return false; }

private:
    Scene* _scene = 0;

};

REGISTERER(Manager)

#define REGISTER_DECL_MANAGAERTYPE(CLASSNAME) \
    static ManagerRegister<CLASSNAME> reg

#define REGISTER_DEFN_MANAGAERTYPE(CLASSNAME) \
    ManagerRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)


#endif // MANAGER_H
