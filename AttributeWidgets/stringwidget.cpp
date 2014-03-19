#include "stringwidget.h"
#include <QLineEdit>
#include "Attributes/stringattribute.h"
#include "ui_stringwidget.h"
#include <QDebug>
#include "testobject.h"

REGISTER_DEFN_ATTRIBUTEWIDGETTYPE(StringWidget);

StringWidget::StringWidget(QList<Attribute*> attributes) : AttributeWidget(attributes), ui(new Ui::StringWidget())
{
    ui->setupUi(this);

    ui->label->setText(((StringAttribute*) attributes.first())->label());


    for (StringAttribute* a : this->attributes<StringAttribute>()) {
        connect(ui->lineEdit, SIGNAL(textChanged(QString)), a, SLOT(setString(QString)));
        connect(a, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

void StringWidget::updateView()
{
    ui->lineEdit->blockSignals(true);
    ui->lineEdit->setText(attributes<StringAttribute>().first()->string());
    for (StringAttribute* a : attributes<StringAttribute>()) {
        if (ui->lineEdit->text() != a->string()) {
            ui->lineEdit->setText(MULTI_LABEL);
            break;
        }
    }
    ui->lineEdit->blockSignals(false);
}
