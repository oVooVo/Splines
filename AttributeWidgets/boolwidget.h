#ifndef BOOLWIDGET_H
#define BOOLWIDGET_H

#include "AttributeWidgets/attributewidget.h"
#include <QCheckBox>


class BoolWidget : public AttributeWidget
{
    Q_OBJECT

public:
    explicit BoolWidget(QList<Attribute*> attributes);
    ~BoolWidget();
    QCheckBox* _checkbox;

private slots:
    void updateView();

    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(BoolWidget);
};

#endif // BOOLWIDGET_H
