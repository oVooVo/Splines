#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include <QTabWidget>
#include <Objects/object.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include "AttributeWidgets/attributewidget.h"
#include "dockablemanager.h"

class AttributeManager : public DockableManager
{
    Q_OBJECT
public:
    explicit AttributeManager(QWidget *parent = 0);

    void selectionChanged();

private:
    void setSelection(QList<Object*> objects);
    QList<QWidget *> getWidgets(QList<Object*> objects);
    QScrollArea* _scrollArea;
    QWidget* _widget = 0;
    REGISTER_DECL_DOCKABLEMANAGERTYPE(AttributeManager);

};

#endif // ATTRIBUTEMANAGER_H
