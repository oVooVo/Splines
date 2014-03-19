#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QObject>
#include "Attributes/attribute.h"
#include <QWidget>


/*
 *  Do not use the register_defines.h registration system because AttributeWidget constructor takes arguments!
 */
class AttributeWidget;
#define ATTRIBUTEWIDGET_CREATOR_MAP_TYPE QMap<QString, AttributeWidget* (*)(QList<Attribute*>&)>
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
    template<typename T = Attribute> QList<T*> attributes() const
    {
        QList<T*> list;
        for (Attribute* a : _attributes) {
            list << a->cast<T>();
        }
        return list;
    }

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

protected:
    static const QString MULTI_LABEL;
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
