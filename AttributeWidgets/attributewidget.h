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

class AttributeWidget : public QObject
{
public:
    explicit AttributeWidget(QList<Attribute*> attributes);
    explicit AttributeWidget();
    QList<Attribute*> attributes() const { return _attributes; }
    virtual QWidget* createWidget(QWidget* parent = 0) const { Q_UNUSED(parent); return new QWidget(); }


private:
    QList<Attribute*> _attributes;

protected:
    static ATTRIBUTEWIDGET_CREATOR_MAP_TYPE *_creatorMap;
public:
    static QWidget *createWidget(QList<Attribute*> attributes);



};

template<typename T>
struct AttributeWidgetRegister : AttributeWidget
{
    AttributeWidgetRegister(QString className) : AttributeWidget()
    {
        if (!_creatorMap)
            _creatorMap = new ATTRIBUTEWIDGET_CREATOR_MAP_TYPE();
        _creatorMap->insert(className, &createAttributeWidget<T>);
    }
};

#define REGISTER_DECL_ATTRIBUTEWIDGETTYPE(CLASSNAME) \
    static AttributeWidgetRegister<CLASSNAME> reg

#define REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(CLASSNAME) \
    AttributeWidgetRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

#endif // ATTRIBUTEWIDGET_H
