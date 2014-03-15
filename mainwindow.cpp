#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Viewport* viewport = new Viewport();


    _scene = new Scene();
    viewport->setScene(_scene);
    ui->treeView->setModel(_scene);

    connect(ui->actionNewSpline, SIGNAL(triggered()), this, SLOT(addSpline()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSpline()
{
    _scene->addObject(new Spline());
}
