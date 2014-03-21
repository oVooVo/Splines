#include "boolwidget.h"
#include <QHBoxLayout>
#include <QDebug>

#include "Attributes/boolattribute.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(BoolWidget);

BoolWidget::BoolWidget(QList<Attribute *> attributes) :
    AttributeWidget(attributes)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    _checkbox = new QCheckBox(this);
    _checkbox->setText(attributes.first()->label());
    layout->addWidget(_checkbox);

    for (BoolAttribute* a : this->attributes<BoolAttribute>()) {
        connect(_checkbox, SIGNAL(toggled(bool)), a, SLOT(setValue(bool)));
        connect(a, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

BoolWidget::~BoolWidget()
{
}

void BoolWidget::updateView()
{
    _checkbox->blockSignals(true);
    _checkbox->setChecked(attributes<BoolAttribute>().first()->value());
    for (BoolAttribute* a : attributes<BoolAttribute>()) {
        if (_checkbox->isChecked() != a->value()) {
            _checkbox->setCheckState(Qt::PartiallyChecked);
            break;
        }
    }
    _checkbox->blockSignals(false);
}

