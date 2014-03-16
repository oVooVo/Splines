#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Viewport* viewport = new Viewport();


    _scene = new Scene();
    viewport->setScene(_scene);
    ui->treeView->setModel(_scene);

    connect(ui->actionNewSpline, &QAction::triggered, [this]() { _scene->addObject(new Spline()); });
    connect(ui->actionSpeichern, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSpeichern_unter, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->action_ffnen, SIGNAL(triggered()), this, SLOT(load()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSpline()
{
    _scene->addObject(new Object());
}

void MainWindow::save()
{
    if (_filepath.isEmpty()) {
        saveAs();
    }

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    stream << _scene;
    file.close();
}

QString MainWindow::fileDialogDirectory() const
{
    return _filepath.isEmpty() ? QDir::home().absolutePath() : _filepath;
}

void MainWindow::saveAs()
{
    _filepath = QFileDialog::getSaveFileName(this, "Save Project", fileDialogDirectory());
    if (!_filepath.isEmpty())
        save();
}

void MainWindow::load()
{
    ui->treeView->setModel(0);
    delete _scene;
    _filepath = QFileDialog::getOpenFileName(this, "Open Project", fileDialogDirectory());

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    stream >> _scene;
    ui->treeView->setModel(_scene);
    file.close();
}
