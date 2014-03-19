#include "attributemanager.h"
#include "AttributeWidgets/attributewidget.h"
#include <QDebug>

REGISTER_DEFN_MANAGAERTYPE(AttributeManager);

AttributeManager::AttributeManager(QWidget *parent) :
    Manager(parent)
{
    _scrollArea = new QScrollArea(this);
    setWidget(_scrollArea);
}

void AttributeManager::setSelection(QList<Object*> objects)
{
    _scrollArea->setWidget(0);
    if (_widget)
        delete _widget; // and all attribute widgets as children
    _widget = new QWidget(_scrollArea);


    QVBoxLayout* layout = new QVBoxLayout(_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    for (QWidget* w : getWidgets(objects)) {
        w->setParent(_widget);
        layout->addWidget(w);
    }


    _widget->setLayout(layout);
    _scrollArea->setWidget(_widget);

}

QList<QWidget*> AttributeManager::getWidgets(QList<Object *> objects)
{
    if (objects.isEmpty()) {
        return QList<QWidget*>();
    }


    // find set keys that includes each QString k, that is an attribute's key in each object in objects
    QList<QString> keys = objects.first()->attributes().keys();
    for (Object* o : objects) {
        for (QString key : keys) {
            if (!o->attributes().keys().contains(key)) {
                keys.removeOne(key);
            }
        }
    }

    //for each key in keys find corresponding attributes for each object in objects
    QList<QList<Attribute*> > attributeLists;
    for (QString key : keys) {
        QList<Attribute*> attributes_with_equal_key;
        for (Object* o : objects) {
            attributes_with_equal_key.append(o->attributes()[key]);
        }
        attributeLists.append(attributes_with_equal_key);
    }

    //now find attributeWidgets for each attribute-list!
    QList<QWidget*> attributeWidgets;
    for (QList<Attribute*> attributes : attributeLists) {
        attributeWidgets.append(AttributeWidget::createWidget(attributes));
    }


    return attributeWidgets;
}

void AttributeManager::setScene(Scene *s)
{
    Manager::setScene(s);
    if (scene()) {
        connect(scene()->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
            setSelection(scene()->selectedObjects());
        });
        setSelection(scene()->selectedObjects());
    }
}
