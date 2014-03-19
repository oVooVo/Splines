#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include "attributewidget.h"
#include "ui_transformationwidget.h"

class TransformationWidget : public AttributeWidget
{
    Q_OBJECT

public:
    explicit TransformationWidget(QList<Attribute *> attributes);

    QWidget* createWidget(QWidget *parent) const;
private slots:
    void updateView();
private:
    Ui::TransformationWidget* ui;

private:
    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(TransformationWidget);


};

#endif // TRANSFORMATIONWIDGET_H
