#include "colorwidget.h"
#include "Attributes/colorattribute.h"
#include "ui_colorwidget.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(ColorWidget);

ColorWidget::ColorWidget(QList<Attribute *> attributes) :
    AttributeWidget(attributes),
    ui(new Ui::ColorWidget)
{
    ui->setupUi(this);
    ui->label->setText(attributes.first()->label());
    for (ColorAttribute* a : this->attributes<ColorAttribute>()) {
        connect(ui->button, SIGNAL(colorChanged(QColor)), a, SLOT(setColor(QColor)));
        connect(a, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::updateView()
{
    ui->button->blockSignals(true);
    ui->button->setColor(attributes<ColorAttribute>().first()->color());
    for (ColorAttribute* a : attributes<ColorAttribute>()) {
        if (ui->button->color() != a->color()) {
            ui->button->setMulti();
            break;
        }
    }
    ui->button->blockSignals(false);
}
