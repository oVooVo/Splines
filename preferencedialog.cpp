#include "preferencedialog.h"
#include "ui_preferencedialog.h"

PreferenceDialog::PreferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(on_accept()));
    ui->point_activeAndSelected->setColor(Preferences::colors.value("Point.active.selected"));
    ui->point_activeAndDeselected->setColor(Preferences::colors.value("Point.active.deselected"));
    ui->point_inactive->setColor(Preferences::colors.value("Point.inactive"));
    ui->tolerance->setValue(Preferences::doubles.value("Grabber.Tolerance"));
    ui->spline_active_end->setColor(Preferences::colors.value("Spline.active.end"));
    ui->spline_active_start->setColor(Preferences::colors.value("Spline.active.start"));
    ui->spline_inactive->setColor(Preferences::colors.value("Spline.inactive"));
    ui->background->setColor(Preferences::colors.value("Background"));
}

PreferenceDialog::~PreferenceDialog()
{
    delete ui;
}

void PreferenceDialog::on_accept()
{
    Preferences::colors.insert("Point.active.selected",
                               ui->point_activeAndSelected->color());
    Preferences::colors.insert("Point.active.deselected",
                               ui->point_activeAndDeselected->color());
    Preferences::colors.insert("Point.inactive",
                               ui->point_inactive->color());
    Preferences::doubles.insert("Grabber.Tolerance",
                                ui->tolerance->value());
    Preferences::colors.insert("Spline.active.start",
                               ui->spline_active_start->color());
    Preferences::colors.insert("Spline.active.end",
                               ui->spline_active_end->color());
    Preferences::colors.insert("Spline.inactive",
                               ui->spline_inactive->color());
    Preferences::colors.insert("Background",
                               ui->background->color());
    Preferences::writeSettings();
}
