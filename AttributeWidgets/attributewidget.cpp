#include "attributewidget.h"
#include <QDebug>
#include <QRegExp>

ATTRIBUTEWIDGET_CREATOR_MAP_TYPE *AttributeWidget::_creatorMap = 0;

AttributeWidget::AttributeWidget(QList<Attribute *> attributes)
{
    _attributes = attributes;
//    for (Attribute* a : _attributes) {

//        // Note: old SIGNAL-SLOT syntax does not work. Apperently at this time, this is a QWidget, not an AttributeWidget so
//        //  QMetablabla cannot determine the correct SLOT. However, when the SIGNAL is raised, this is an AttributeWidget so
//        //  the call is safe.
//        connect(a, &Attribute::changed, [this]() {
//            qDebug() << "blublub";
//            qDebug() << "call update View" << metaObject()->className();
//            updateView();
//        });
//    }
}

QWidget* AttributeWidget::createWidget(QList<Attribute *> attributes)
{
    Q_ASSERT_X(!attributes.isEmpty(), "AttributeWidget::AttributeWidget", "attribute list must not be empty");
    QString classname = attributes.first()->metaObject()->className();

    for (Attribute* attribute : attributes) {
        Q_ASSERT_X(QString(attribute->metaObject()->className()) == classname,
                   "AttributeWidget::AttributeWidget",
                   "attributes in attribute list must be from same type");
    }

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
