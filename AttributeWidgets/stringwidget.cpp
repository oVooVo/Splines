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


    for (Attribute* a : attributes) {
        StringAttribute* sa = (StringAttribute*) a;
        connect(ui->lineEdit, SIGNAL(textChanged(QString)), sa, SLOT(setString(QString)));
        connect(sa, SIGNAL(changed()), this, SLOT(updateView()));
    }
    updateView();
}

void StringWidget::updateView()
{
    ui->lineEdit->blockSignals(true);
    ui->lineEdit->setText(((StringAttribute*) attributes().first())->string());
    for (Attribute* a : attributes()) {
        StringAttribute* sa = (StringAttribute*) a;
        if (ui->lineEdit->text() != sa->string()) {
            ui->lineEdit->setText(MULTI_LABEL);
            break;
        }
    }
    ui->lineEdit->blockSignals(false);
}
