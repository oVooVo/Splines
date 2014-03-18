#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include <QTabWidget>
#include <Objects/object.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include "AttributeWidgets/attributewidget.h"

class AttributeManager : public QWidget
{
    Q_OBJECT
public:
    explicit AttributeManager(QWidget *parent = 0);

    void setSelection(QList<Object*> objects);
private:
    QList<QWidget *> getWidgets(QList<Object*> objects);
    QScrollArea* _scrollArea;
    QWidget* _widget = 0;

};

#endif // ATTRIBUTEMANAGER_H
