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
     * @brief isCheckable returns whether this action checkable
     * @return whether this action is checkable
     */
    virtual bool isCheckable() const = 0;

    /**
     * @brief makeAction returns whether an action should be created from this object
     * @return whether an action should be created from this object
     *  Note: this flag is only a hint for the view, not definite.
     */
    virtual bool makeAction() const { return true; }

};

#endif // ACTION_H
