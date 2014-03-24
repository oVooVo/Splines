#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "register_defines.h"

/**
 * @brief The Attribute class provides an interface for Attributes. They can be serialized and deserialized
 *  in an easy way. Derived Attributes should be registered as told in register_defines.h
 */
class Attribute : public QObject
{
    Q_OBJECT
    DECL_MEMBER(Attribute)

public:
    Attribute(QString label = "Label");
    template<typename T> T* cast() const  { return (T*) this; }

    /*
     * Introduce a macro to simplify (de)serialization
     * in any derived Attribute class, you need to overwrite
     *          void registerAttributeData(QDataStream& stream, Direction direction)
     * and register all data that should be (de)serialized.
     * Lets assume there is a QImage named _image that you want to be saved and restored
     * automatically in an ImageAttribute, then overwrite registerAttributeData and write
     *      Register(_image)
     */
protected:
    enum Direction { Serialize, Deserialize };
#define REGISTER_DATA(data)         \
    if (direction == Serialize) {   \
        stream << (data);           \
    } else {                        \
        stream >> (data);           \
    }
    virtual void registerAttributeData(QDataStream& stream, Direction direction) {
        Q_UNUSED(direction);
        Q_UNUSED(stream);
    }

    /*
     * Encode value in a string to save the data in a human readable format
     */
public:
    virtual void fromString(QString string) = 0;
    virtual QString toString() const = 0;

signals:
    /**
     * @brief changed is emitted whenever this attribute changes.
     */
    void changed();

    friend QDataStream& operator<<(QDataStream& out, const Attribute* a);
    friend QDataStream& operator>>(QDataStream& in,  Attribute* &a);

private:
    // every attribute has a label representing the role of the value.
    QString _label;
public:
    QString label() const { return _label; }

};

REGISTERER(Attribute)


QDataStream& operator<<(QDataStream& out, const Attribute* a);
QDataStream& operator>>(QDataStream& in,  Attribute* &a);

#endif // ATTRIBUTE_H
