#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include <QWidget>
#include "../Attributes/transformationattribute.h"
#include "../Attributes/attribute.h"

namespace Ui {
class TransformationWidget;
}

class TransformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformationWidget(QList<Attribute *> attributes, QWidget *parent = 0);
    ~TransformationWidget();

private:
    Ui::TransformationWidget *ui;
    QList<Attribute*> _attributes;
private slots:
    void updateView();
};

#endif // TRANSFORMATIONWIDGET_H
