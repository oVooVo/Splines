#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QIcon>

/**
 * @brief The Action class provides an interface for registered classes to generate QAction automatically.
 *  therefore the attributes for QAction are defined here virtually.
 */
class Action
{
protected:
    Action() {}
public:
    virtual ~Action() {}

public:
    /**
     * @brief actionText returns the text that this action shows
     * @return the text that this action shows
     */
    virtual QString actionText() const = 0;

    /**
     * @brief toolTip returns the toolTip from this action
     * @return the toolTip from this action
     */
    virtual QString toolTip() const = 0;

    /**
     * @brief icon returns the icon from this action
     * @return the icon of this action
     */
    virtual QIcon icon() const = 0;

    /**
     * @brief isCommand returns whether this action is a command. Commands are performed when they are activated.
     *  In contrast to commands there are tools that can be activated but are perfomed interactively.
     * @return whether this action is is a command
     */
    virtual bool isCommand() const = 0;

    /**
     * @brief makeAction returns whether an action should be created from this object
     * @return whether an action should be created from this object
     *  Note: this flag is only a hint for the view, not definite.
     */
    virtual bool makeAction() const { return true; }

};

#endif // ACTION_H
