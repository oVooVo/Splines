#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QObject>
#include "Attributes/attribute.h"
#include <QWidget>


class AttributeWidget;
// convienience define to save typing the type often
#define ATTRIBUTEWIDGET_CREATOR_MAP_TYPE QMap<QString, AttributeWidget* (*)(QList<Attribute*>&)>

//creates a new AttributeWidget of Type T out of a given attributeList.
template<typename T> AttributeWidget *createAttributeWidget(QList<Attribute*> &attributes) { return new T(attributes); }


/**
 * @brief The AttributeWidget class abstract class. Every user interface for attributes should inherit this class.
 */
class AttributeWidget : public QWidget
{
public:
    /**
     * @brief AttributeWidget creates a new AttributeWidget out of given attributes.
     * @param attributes the attributes this Widget ist connected to
     */
    explicit AttributeWidget(QList<Attribute*> attributes);

    /**
     * @brief attributes returns the attributes this widget is connected to
     * @return the attributes this widget is connected to
     */
    QList<Attribute*> attributes() const { return _attributes; }

private:
    /**
     * @brief _attributes the attributes this widget is connected to
     */
    QList<Attribute*> _attributes;

public:
    /**
     * @brief createWidget creates a new widget out of given attributes.
     *  Uses the registration system of AttributeWidget to determine constructor of the corresponding attributes.
     * @param attributes the attributes the new widget is created from.
     *  All attributes entries must be from same type.
     * @return
     */
    static QWidget *createWidget(QList<Attribute*> attributes);

private:
    /**
     * @brief _creatorMap saves the constructors of the AttributeWidget
     */
    static ATTRIBUTEWIDGET_CREATOR_MAP_TYPE *_creatorMap;

    //allows to keep _creatorMap private since _creatorMap is an implementation detail.
    template<typename T> friend class AttributeWidgetRegister;

};

/**
 * registers all AttributeWidget classnames on program start. Note: AttributeWidgetRegister must not inherit AttributeWidget since
 * AttributeWidget inherits QWidget and QWidgets cannot be created without QApplication but AttributeWidgetRegister must be created
 * statically on very begin.
 */
template<typename T>
struct AttributeWidgetRegister
{
    AttributeWidgetRegister(QString className)
    {
        if (!AttributeWidget::_creatorMap)  //create new _creatorMap if there wasnt one.
            AttributeWidget::_creatorMap = new ATTRIBUTEWIDGET_CREATOR_MAP_TYPE();
        // insert constructor of registered type with classname-key.
        AttributeWidget::_creatorMap->insert(className, &createAttributeWidget<T>);
    }
};

#define REGISTER_DECL_ATTRIBUTEWIDGETTYPE(CLASSNAME) \
    static AttributeWidgetRegister<CLASSNAME> reg

#define REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(CLASSNAME) \
    AttributeWidgetRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

#endif // ATTRIBUTEWIDGET_H
