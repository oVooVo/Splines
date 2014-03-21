#ifndef TOOL_H
#define TOOL_H

#include "Objects/object.h"
#include "interaction.h"
#include <QObject>
#include "action.h"
#include "register_defines.h"
#include <QWidget>

#define CLASSNAME(CLASS) CLASS::staticMetaObject.className()

/**
 * @brief The Tool class
 */
class Tool : public QObject, public Action
{
    Q_OBJECT
    DECL_MEMBER(Tool)
public:
    Tool();

    void perform(Object* o);
    void setParentWidget(QWidget* widget) { _parentWidget = widget; }
    QWidget* parentWidget() const { return _parentWidget; }
    void config(const Interaction &interaction);

    Interaction interaction(Object* o = 0) const;

    virtual QString actionText() const { return QString(metaObject()->className()); }
    virtual QString toolTip() const { return QString(); }
    virtual QIcon icon() const { return QIcon(); }

protected:
    virtual bool canPerform(const Object* o) const = 0;
    virtual void perform_virtual(Object* o) = 0;


private:
    Interaction _interaction;
    QWidget* _parentWidget = 0;

};

REGISTERER(Tool)

#endif // TOOL_H
