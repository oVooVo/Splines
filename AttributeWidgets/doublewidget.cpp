#include "doublewidget.h"
#include "ui_doublewidget.h"
#include "Attributes/doubleattribute.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(DoubleWidget);

DoubleWidget::DoubleWidget(QList<Attribute *> attributes) :
    AttributeWidget(attributes),
    ui(new Ui::DoubleWidget)
{
    ui->setupUi(this);
    ui->label->setText(attributes.first()->label());
    for (DoubleAttribute* a : this->attributes<DoubleAttribute>()) {
        connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), a, SLOT(setValue(double)));
        connect(a, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

DoubleWidget::~DoubleWidget()
{
    delete ui;
}

void DoubleWidget::updateView()
{
    ui->doubleSpinBox->blockSignals(true);
    ui->doubleSpinBox->setValue(attributes<DoubleAttribute>().first()->value());
    for (DoubleAttribute* a : attributes<DoubleAttribute>()) {
        if (!qFuzzyCompare(ui->doubleSpinBox->value(), a->value())) {
            ui->doubleSpinBox->setValue(ui->doubleSpinBox->minimum());
            break;
        }
    }
    ui->doubleSpinBox->blockSignals(false);
}
