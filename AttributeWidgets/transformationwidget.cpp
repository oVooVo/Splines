#include "transformationwidget.h"
#include "ui_transformationwidget.h"
#include <QDebug>

TransformationWidget::TransformationWidget(QList<Attribute *> attributes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformationWidget)
{
    ui->setupUi(this);
    _attributes = attributes;
    for (Attribute* ta : _attributes) {
        Q_ASSERT_X(ta->inherits(TransformationAttribute::staticMetaObject.className()), "TransformationWidget::TransformationWidget",
                   "Trying to create TransformationWidget from non TransformationAttribute");
        // View --> Model
        connect(ui->doubleSpinBoxR,  SIGNAL(valueChanged(double)), ta, SLOT(setR(qreal)));
        connect(ui->doubleSpinBoxX,  SIGNAL(valueChanged(double)), ta, SLOT(setX(qreal)));
        connect(ui->doubleSpinBoxY,  SIGNAL(valueChanged(double)), ta, SLOT(setY(qreal)));
        connect(ui->doubleSpinBoxSX, SIGNAL(valueChanged(double)), ta, SLOT(setSX(qreal)));
        connect(ui->doubleSpinBoxSY, SIGNAL(valueChanged(double)), ta, SLOT(setSY(qreal)));

        // Model --> View
        connect(ta, SIGNAL(rChanged(qreal)),  this, SLOT(updateView()));
        connect(ta, SIGNAL(xChanged(qreal)),  this, SLOT(updateView()));
        connect(ta, SIGNAL(yChanged(qreal)),  this, SLOT(updateView()));
        connect(ta, SIGNAL(sxChanged(qreal)), this, SLOT(updateView()));
        connect(ta, SIGNAL(syChanged(qreal)), this, SLOT(updateView()));
    }
    updateView();
}

TransformationWidget::~TransformationWidget()
{
    delete ui;
}

void TransformationWidget::updateView()
{
    if (_attributes.isEmpty()) {
        ui->doubleSpinBoxR->setSpecialValueText("Nothing Selected");
        ui->doubleSpinBoxR->setEnabled(false);
        ui->doubleSpinBoxX->setSpecialValueText("Nothing Selected");
        ui->doubleSpinBoxX->setEnabled(false);
        ui->doubleSpinBoxY->setSpecialValueText("Nothing Selected");
        ui->doubleSpinBoxY->setEnabled(false);
        ui->doubleSpinBoxSX->setSpecialValueText("Nothing Selected");
        ui->doubleSpinBoxSX->setEnabled(false);
        ui->doubleSpinBoxSY->setSpecialValueText("Nothing Selected");
        ui->doubleSpinBoxSY->setEnabled(false);
        return;
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
        qreal v = ((TransformationAttribute*) _attributes.first())->value(key);
        spinbox(key)->setValue(v);
        for (Attribute* a : _attributes) {
            if (!qFuzzyCompare(((TransformationAttribute*) a)->value(key), v)) {
                spinbox(key)->setSpecialValueText("< multi >");
                spinbox(key)->setValue(spinbox(key)->minimum());
                break;
            }
        }
    }
}
