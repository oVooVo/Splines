#include "attributewidget.h"
#include <QDebug>
#include <QRegExp>

ATTRIBUTEWIDGET_CREATOR_MAP_TYPE *AttributeWidget::_creatorMap = 0;

const QString AttributeWidget::MULTI_LABEL = "<< multi >>";

AttributeWidget::AttributeWidget(QList<Attribute *> attributes)
{
    _attributes = attributes;
}

QWidget* AttributeWidget::createWidget(QList<Attribute *> attributes)
{
    Q_ASSERT_X(!attributes.isEmpty(), "AttributeWidget::AttributeWidget", "attribute list must not be empty");
    QString classname = attributes.first()->metaObject()->className();

    // Ensure that each Attribute has a corresponding AttributeWidget.
    // AttributeWidget must have same classname as Attribute -"Attribute" + "Widget"
    // for example, "TransformationAttribute" -> "TransformationWidget"
    // what a hack!!! :)

    const QRegExp attribute_s = QRegExp("Attribute$");
    const QString widget_s    = "Widget";

    Q_ASSERT_X(classname.contains(attribute_s), "AttributeWidget::createWidget",
               QString("classname should contain").arg(attribute_s.pattern()).toStdString().c_str());

    classname = classname.replace(attribute_s, widget_s);

    QWidget* widget = 0;
    ATTRIBUTEWIDGET_CREATOR_MAP_TYPE::Iterator it = _creatorMap->find(classname);
    if (it != _creatorMap->end()) {
        widget = (it.value())(attributes);
    }

    if (!widget) {
        qWarning() << "Warning: Classname " << classname << "not found.";
        Q_ASSERT_X(widget, "Object::deserialize", "deserialization failed.");
    }

    return widget;
}
