#include "attributemanager.h"
#include "AttributeWidgets/transformationwidget.h"
#include <QDebug>

AttributeManager::AttributeManager(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* l = new QVBoxLayout(this);
    _scrollArea = new QScrollArea(this);
    l->setContentsMargins(0, 0, 0, 0);
    l->addWidget(_scrollArea);
    setLayout(l);
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
    auto checkInheritance = [objects](const char* classname) {
        for (Object* o : objects) {
            if (!o->inherits(classname))
                return false;
        }
        return true;
    };

    const QMetaObject* candidateClass = objects.first()->metaObject();

    while (!checkInheritance(candidateClass->className())) {
        candidateClass = candidateClass->superClass();
    }

    qDebug() << "tgv = " << QString(candidateClass->className());


    QList<QList<Attribute*> > attributes;
    QList<QWidget*> attributeWidgets;

    for (QString key : Object::attributeKeys(QString(candidateClass->className()))) {
        qDebug() << "key: " << key;
        QList<Attribute*> attr;
        for (Object* o : objects) {
            qDebug() << "key = " << key;
            Q_ASSERT_X(o->attributes()[key], "AttributeManager::getWidgets", "attributes is null");
            attr.append(o->attributes()[key]);
        }
        attributes.append(attr);
    }

    for (QList<Attribute*> attr : attributes) {
        QString classname = QString(attr.first()->metaObject()->className());
        if (classname == TransformationAttribute::staticMetaObject.className()) {
            attributeWidgets.append(new TransformationWidget(attr));
        }
    }
    return attributeWidgets;
}
