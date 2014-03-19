#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include <QTabWidget>
#include <Objects/object.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include "AttributeWidgets/attributewidget.h"
#include "manager.h"

class AttributeManager : public Manager
{
    Q_OBJECT
public:
    explicit AttributeManager(QWidget *parent = 0);
    void setScene(Scene *s);

private:
    void setSelection(QList<Object*> objects);
    QList<QWidget *> getWidgets(QList<Object*> objects);
    QScrollArea* _scrollArea;
    QWidget* _widget = 0;
    REGISTER_DECL_MANAGAERTYPE(AttributeManager);

};

#endif // ATTRIBUTEMANAGER_H
