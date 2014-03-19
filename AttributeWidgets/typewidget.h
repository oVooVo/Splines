#ifndef TYPEWIDGET_H
#define TYPEWIDGET_H

#include <QWidget>
#include "attributewidget.h"
#include "Attributes/typeattribute.h"

namespace Ui {
class TypeWidget;
}

class TypeWidget : public AttributeWidget
{
    Q_OBJECT

public:
    explicit TypeWidget(QList<Attribute*> attributes);
    ~TypeWidget();
private slots:
    void updateView();

private:
    Ui::TypeWidget *ui;
    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(TypeWidget);
};

#endif // TYPEWIDGET_H
