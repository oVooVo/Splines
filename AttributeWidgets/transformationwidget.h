#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include "attributewidget.h"
#include <QWidget>
#include "Attributes/transformationattribute.h"
#include "Attributes/attribute.h"

namespace Ui {
class TransformationWidget;
}

class TransformationWidget : public AttributeWidget
{
    Q_OBJECT

public:
    explicit TransformationWidget(QList<Attribute *> attributes);
    ~TransformationWidget();
    QWidget* createWidget(QWidget *parent) const;

private slots:
    void updateView();

private:
    REGISTER_DECL_ATTRIBUTEWIDGETTYPE(TransformationWidget);

};

#endif // TRANSFORMATIONWIDGET_H
