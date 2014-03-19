#ifndef STRINGWIDGET_H
#define STRINGWIDGET_H

#include "attributewidget.h"
#include "ui_stringwidget.h"



class StringWidget : public AttributeWidget
{
    Q_OBJECT
public:
    StringWidget(QList<Attribute*> attributes);

private slots:
    void updateView();

private:
    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(StringWidget);
    Ui::StringWidget* ui;
};

#endif // STRINGWIDGET_H
