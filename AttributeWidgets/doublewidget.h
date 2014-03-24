#ifndef DOUBLEWIDGET_H
#define DOUBLEWIDGET_H

#include "attributewidget.h"

namespace Ui {
class DoubleWidget;
}

class DoubleWidget : public AttributeWidget
{
    Q_OBJECT

public:
    explicit DoubleWidget(QList<Attribute*> attributes);
    ~DoubleWidget();

private slots:
    void updateView();

private:
    Ui::DoubleWidget *ui;
    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(DoubleWidget);
};

#endif // DOUBLEWIDGET_H
