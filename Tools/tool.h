#ifndef TOOL_H
#define TOOL_H

#include "Objects/object.h"
#include "interaction.h"
#include <QObject>
#include <QIcon>


class Tool;
#define TOOL_CREATOR_MAP_TYPE QMap<QString, Tool* (*)()>
template<typename T> Tool *createTool() { return new T(); }

class Tool : public QObject
{
    Q_OBJECT
public:
    Tool();

    virtual void perform(Object* o) = 0;
    void config(Interaction& interaction);

    Interaction interaction() const { return _interaction; }

    /*
     * Following might hurt Model <-> View, but i guess its the most convienient... */
    virtual QString name() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); } /*
     *
     */

    static TOOL_CREATOR_MAP_TYPE* creatorMap() { return _creatorMap; }
    static Tool *createInstance(QString className);


private:
    Interaction _interaction;

private:
    template<typename T> friend class ToolRegister;
    static TOOL_CREATOR_MAP_TYPE *_creatorMap;

};

template<typename T>
struct ToolRegister
{
    ToolRegister(QString className)
    {
        if (!Tool::_creatorMap)
            Tool::_creatorMap = new TOOL_CREATOR_MAP_TYPE();
        Tool::_creatorMap->insert(className, &createTool<T>);
    }
};

#define REGISTER_DECL_TOOLTYPE(CLASSNAME) \
    static ToolRegister<CLASSNAME> reg

#define REGISTER_DEFN_TOOLTYPE(CLASSNAME) \
    ToolRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

#endif // TOOL_H
