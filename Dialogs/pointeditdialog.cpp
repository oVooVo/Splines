#include "pointeditdialog.h"
#include "ui_pointeditdialog.h"
#include <QDebug>

PointEditDialog::PointEditDialog(Point *p, bool tangents, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditDialog)
{
    ui->setupUi(this);
    _tangents = tangents;
    _point = p;
    ui->doubleSpinBoxX->setValue(p->point().x());
    ui->doubleSpinBoxY->setValue(p->point().y());
    if (tangents) {
        ui->doubleSpinBoxLeftX->setValue(p->left().x());
        ui->doubleSpinBoxLeftY->setValue(p->left().y());
        ui->doubleSpinBoxRightX->setValue(p->right().x());
        ui->doubleSpinBoxRightY->setValue(p->right().y());
    } else {
        ui->groupBoxLeft->setEnabled(false);
        ui->groupBoxRight->setEnabled(false);
    }
    connect(this, SIGNAL(accepted()), this, SLOT(on_accept()));
}

PointEditDialog::~PointEditDialog()
{
    delete ui;
}

QPointF PointEditDialog::point() const
{
    return QPointF(
                ui->doubleSpinBoxX->value(),
                ui->doubleSpinBoxY->value());
}

QPointF PointEditDialog::left() const
{
    return QPointF(
                ui->doubleSpinBoxLeftX->value(),
                ui->doubleSpinBoxLeftY->value());
}

QPointF PointEditDialog::right() const
{
    return QPointF(
                ui->doubleSpinBoxRightX->value(),
                ui->doubleSpinBoxRightY->value());
}

void PointEditDialog::on_accept()
{
    _point->setPoint(QPointF(
                         ui->doubleSpinBoxX->value(),
                         ui->doubleSpinBoxY->value()));
    if (_tangents) {
        _point->setTangent(
                    QPointF(
                        ui->doubleSpinBoxLeftX->value(),
                        ui->doubleSpinBoxLeftY->value()),
                    QPointF(
                        ui->doubleSpinBoxRightX->value(),
                        ui->doubleSpinBoxRightY->value()));
    }
}

bool PointEditDialog::exec_static(Point *p, bool tangents, QWidget *parents)
{
    PointEditDialog* dialog = new PointEditDialog(p, tangents, parents);
    bool code = dialog->exec();
    delete dialog;
    return code;
}
