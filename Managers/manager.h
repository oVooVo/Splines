#ifndef MANAGER_H
#define MANAGER_H

#include <QDockWidget>
#include "scene.h"
#include <QIcon>

class Manager;
#define MANAGER_CREATOR_MAP_TYPE QMap<QString, Manager* (*)(QWidget*)>
template<typename T> Manager *createManager(QWidget* parent) { return new T(parent); }

class Manager : public QDockWidget
{
    Q_OBJECT
public:
    Manager(QWidget* parent = 0);

public:
    Scene* scene() const { return _scene; }
    virtual void setScene(Scene* s);

    static MANAGER_CREATOR_MAP_TYPE* creatorMap() { return _creatorMap; }
    static Manager *createInstance(QString classname, QWidget* parent = 0);
    static QStringList types() { return creatorMap()->keys(); }

    //TODO same methodes in Tool => ...
    virtual QString name() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }

private:
    Scene* _scene;

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
