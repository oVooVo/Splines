#ifndef MANAGER_H
#define MANAGER_H

#include <QDockWidget>
#include "scene.h"
#include <QIcon>
#include <action.h>

class Manager;
#define MANAGER_CREATOR_MAP_TYPE QMap<QString, Manager* (*)(QWidget*)>
template<typename T> Manager *createManager(QWidget* parent) { return new T(parent); }

class Manager : public QDockWidget, public Action
{
    Q_OBJECT
public:
    Manager(QWidget* parent = 0);

public:
    Scene* scene() const { return _scene; }
    virtual void setScene(Scene* s);

    static Manager *createInstance(QString classname, QWidget* parent = 0);

    //TODO same methodes in Tool => ...
    virtual QString actionText() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }
    bool isCheckable() const { return false; }
    static QStringList types() { return _creatorMap->keys(); }

private:
    Scene* _scene = 0;

protected:
    static MANAGER_CREATOR_MAP_TYPE *_creatorMap;
    template<typename T> friend class ManagerRegister;

};

template<typename T>
struct ManagerRegister
{
    ManagerRegister(QString className)
    {
        if (!Manager::_creatorMap)
            Manager::_creatorMap = new MANAGER_CREATOR_MAP_TYPE();
        Manager::_creatorMap->insert(className, &createManager<T>);
    }
};

#define REGISTER_DECL_MANAGAERTYPE(CLASSNAME) \
    static ManagerRegister<CLASSNAME> reg

#define REGISTER_DEFN_MANAGAERTYPE(CLASSNAME) \
    ManagerRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)


#endif // MANAGER_H
