#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include "AttributeWidgets/attributewidget.h"


namespace Ui {
class ColorWidget;
}

class ColorWidget : public AttributeWidget
{
    Q_OBJECT

public:
    explicit ColorWidget(QList<Attribute*> attributes);
    ~ColorWidget();

private:
    Ui::ColorWidget *ui;
    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(ColorWidget);

private slots:
    void updateView();
};

#endif // COLORWIDGET_H
