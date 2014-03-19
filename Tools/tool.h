#ifndef TOOL_H
#define TOOL_H

#include "Objects/object.h"
#include "interaction.h"
#include <QObject>
#include "action.h"
#include "register_defines.h"


class Tool : public QObject, public Action
{
    Q_OBJECT
    DECL_MEMBER(Tool)
public:
    Tool();

    virtual void perform(Object* o) = 0;
    void config(Interaction& interaction);

    Interaction interaction() const { return _interaction; }

    virtual QString actionText() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }
    bool isCheckable() const { return true; }

private:
    Interaction _interaction;

};

REGISTERER(Tool)

#endif // TOOL_H
