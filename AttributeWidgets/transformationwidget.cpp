#include "transformationwidget.h"
#include "Attributes/transformationattribute.h"
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include "ui_transformationwidget.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(TransformationWidget);

TransformationWidget::TransformationWidget(QList<Attribute *> attributes) :
    AttributeWidget(attributes), ui(new Ui::TransformationWidget())
{
    ui->setupUi(this);

    for (Attribute* a : attributes) {
        TransformationAttribute* ta = (TransformationAttribute*) a;
        connect(ui->doubleSpinBoxR,  SIGNAL(valueChanged(double)), ta, SLOT(setR(double)));
        connect(ui->doubleSpinBoxX,  SIGNAL(valueChanged(double)), ta, SLOT(setX(double)));
        connect(ui->doubleSpinBoxY,  SIGNAL(valueChanged(double)), ta, SLOT(setY(double)));
        connect(ui->doubleSpinBoxSX, SIGNAL(valueChanged(double)), ta, SLOT(setSX(double)));
        connect(ui->doubleSpinBoxSY, SIGNAL(valueChanged(double)), ta, SLOT(setSY(double)));
        connect(ta, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

void TransformationWidget::updateView()
{
    if (attributes().isEmpty()) {
        Q_ASSERT_X(false, "TransformationWidget::createWidget::updateView", "attributes must not be empty");
    }

    auto spinbox = [this](TransformationAttribute::Key key) {
        switch (key) {
        case TransformationAttribute::R: return ui->doubleSpinBoxR;
        case TransformationAttribute::X: return ui->doubleSpinBoxX;
        case TransformationAttribute::Y: return ui->doubleSpinBoxY;
        case TransformationAttribute::SX: return ui->doubleSpinBoxSX;
        case TransformationAttribute::SY: return ui->doubleSpinBoxSY;
        }
        return (QDoubleSpinBox*) 0;
    };

    for (int i = TransformationAttribute::Key_first; i <= TransformationAttribute::Key_last; i++) {
        TransformationAttribute::Key key = (TransformationAttribute::Key) i;
        spinbox(key)->blockSignals(true);
        double v = ((TransformationAttribute*) attributes().first())->value(key);
        spinbox(key)->setValue(v);
        for (Attribute* a : attributes()) {
            if (!qFuzzyCompare(((TransformationAttribute*) a)->value(key), v)) {
                spinbox(key)->setSpecialValueText(MULTI_LABEL);
                spinbox(key)->setValue(spinbox(key)->minimum());
                break;
            }
        }
        spinbox(key)->blockSignals(false);
    }
}
