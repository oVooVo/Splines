#include "typewidget.h"
#include "ui_typewidget.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(TypeWidget);

TypeWidget::TypeWidget(QList<Attribute *> attributes) :
    AttributeWidget(attributes),
    ui(new Ui::TypeWidget)
{
    ui->setupUi(this);

    ui->label->setText(((TypeAttribute*) attributes.first())->label());

    ui->comboBox->addItems(((TypeAttribute*) attributes.first())->types());

    for (Attribute* a : attributes) {
        TypeAttribute* ta = (TypeAttribute*) a;
        connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), ta, SLOT(setCurrentIndex(int)));
        connect(ta, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

TypeWidget::~TypeWidget()
{
    delete ui;
}

void TypeWidget::updateView()
{
    ui->comboBox->blockSignals(true);
    ui->comboBox->setCurrentIndex(((TypeAttribute*) attributes().first())->currentIndex());
    for (Attribute* a : attributes()) {
        TypeAttribute* ta = (TypeAttribute*) a;
        if (ui->comboBox->currentIndex() != ta->currentIndex()) {
            ui->comboBox->setCurrentIndex(-1);
            break;
        }
    }
    ui->comboBox->blockSignals(false);
}
