#ifndef INTERACTION_H
#define INTERACTION_H
#include <QPointF>
#include <QTransform>
#include <QtGlobal>

class Interaction
{

public:
    enum Click       { NoClick, SingleClick, DoubleClick };
    enum Type        { Release, Move, Press, Invalid     };

    Interaction(Qt::MouseButton button, QPointF pos, Type type, Click click = SingleClick, Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    Interaction(QPointF t, Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    Interaction() {}

    static const Interaction NoInteraction;

public:
    // map them to what ever you want :)
    Click click() const {
        return _click;
    }
    Qt::KeyboardModifiers modifiers() const {
        return _modifiers;
    }
    Qt::MouseButton button() const {
        return _button;
    }
    /**
     * @brief point returns the position of the interaction if it is a press or release interaction, translation if it is a move interaction
     * @return the position of the interaction if it is a press or release interaction, translation if it is a move interaction
     */
    QPointF point() const {
        return _point;
    }
    Type type() const {
        return _type;
    }
    bool isValid() const { return _type != Invalid; }

    //map translation into other coordinate system
    void map(QTransform t);

    //return copy of this with mapped transformation
    Interaction mapCopy(QTransform t) const;

    Qt::MouseButtons pressedButtons() const { return _buttonsDown; }

private:
    Click                 _click     = NoClick;
    Qt::KeyboardModifiers _modifiers = Qt::NoModifier;
    Qt::MouseButton       _button    = Qt::NoButton;
    QPointF               _point     = QPointF();
    Type                  _type      = Invalid;
    static Qt::MouseButtons _buttonsDown;
};

#endif // INTERACTION_H
