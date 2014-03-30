#ifndef DOCKABLEMANAGER_H
#define DOCKABLEMANAGER_H

#include <QDockWidget>
#include "scene.h"
#include <QIcon>
#include <action.h>
#include "manager.h"

class DockableManager : public QDockWidget, public Action, public Manager
{
    Q_OBJECT
    DECL_MEMBER(DockableManager)
public:
    DockableManager(QWidget* parent = 0);
    virtual ~DockableManager();

    virtual QString actionText() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }
    bool isCommand() const { return true; } // add new Manager is a command



protected:
    void closeEvent(QCloseEvent *event);


};

REGISTERER(DockableManager)

#define REGISTER_DECL_DOCKABLEMANAGERTYPE(CLASSNAME) \
    static DockableManagerRegister<CLASSNAME> reg

#define REGISTER_DEFN_DOCKABLEMANAGERTYPE(CLASSNAME) \
    DockableManagerRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)


#endif // DOCKABLEMANAGER_H
