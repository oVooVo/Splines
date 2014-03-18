#include "transformationwidget.h"
#include "ui_transformationwidget.h"
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include "ui_transformationwidget.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(TransformationWidget);

TransformationWidget::TransformationWidget(QList<Attribute *> attributes) :
    AttributeWidget(attributes)
{
    /*
    setupUi(this);
    */
}

TransformationWidget::~TransformationWidget()
{
}

void TransformationWidget::updateView()
{
    /*

    */
}

QWidget* TransformationWidget::createWidget(QWidget* parent) const
{
    QWidget* widget = new QWidget(parent);
    Ui::TransformationWidget* ui = new Ui::TransformationWidget();
    ui->setupUi(widget);

    auto updateView = [this, ui]() {
        if (attributes().isEmpty()) {
            Q_ASSERT_X(false, "TransformationWidget::createWidget::updateView", "attributes must not be empty");
        }

        auto spinbox = [this, ui](TransformationAttribute::Key key) {
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
            double v = ((TransformationAttribute*) attributes().first())->value(key);
            spinbox(key)->setValue(v);
            for (Attribute* a : attributes()) {
                if (!qFuzzyCompare(((TransformationAttribute*) a)->value(key), v)) {
                    spinbox(key)->setSpecialValueText("< multi >");
                    spinbox(key)->blockSignals(true);
                    spinbox(key)->setValue(spinbox(key)->minimum());
                    spinbox(key)->blockSignals(false);
                    break;
                }
            }
        }
    };

    for (Attribute* ta : attributes()) {
        Q_ASSERT_X(ta->inherits(TransformationAttribute::staticMetaObject.className()), "TransformationWidget::TransformationWidget",
                   "Trying to create TransformationWidget from non TransformationAttribute");
        // View --> Model
        connect(ui->doubleSpinBoxR,  SIGNAL(valueChanged(double)), ta, SLOT(setR(double)));
        connect(ui->doubleSpinBoxX,  SIGNAL(valueChanged(double)), ta, SLOT(setX(double)));
        connect(ui->doubleSpinBoxY,  SIGNAL(valueChanged(double)), ta, SLOT(setY(double)));
        connect(ui->doubleSpinBoxSX, SIGNAL(valueChanged(double)), ta, SLOT(setSX(double)));
        connect(ui->doubleSpinBoxSY, SIGNAL(valueChanged(double)), ta, SLOT(setSY(double)));

        // Model --> View
        connect(ta, SIGNAL(rChanged(double)),  this, SLOT(updateView()));
        connect(ta, SIGNAL(xChanged(double)),  this, SLOT(updateView()));
        connect(ta, SIGNAL(yChanged(double)),  this, SLOT(updateView()));
        connect(ta, SIGNAL(sxChanged(double)), this, SLOT(updateView()));
        connect(ta, SIGNAL(syChanged(double)), this, SLOT(updateView()));
    }
    updateView();


    return widget;
}
