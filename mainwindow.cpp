#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "Tools/tool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _scene = new Scene();

    ui->viewport->setScene(_scene);
    ui->treeView->setModel(_scene);

    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, [this](){
       QList<Object*> selection;
       for (QModelIndex i : ui->treeView->selectionModel()->selection().indexes())
           selection.append(ui->treeView->model()->getObject(i));
       ui->attributeManager->setSelection(selection);
    });
    connect(ui->actionNewSpline, &QAction::triggered, [this]() { _scene->addObject(new Spline()); });
    connect(ui->actionSpeichern, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSpeichern_unter, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->action_ffnen, SIGNAL(triggered()), this, SLOT(load()));
    connect(_scene, SIGNAL(changed()), ui->treeView, SLOT(update()));

    createToolMenu();
    menuBar()->addMenu(_toolMenu);
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
    _filepath = QFileDialog::getOpenFileName(this, "Open Project", fileDialogDirectory());
    if (_filepath.isEmpty()) return;

    ui->treeView->setModel(0);
    ui->viewport->setScene(0);

    //TODO encapsulate this to provide multiple attribute managers!
    ui->attributeManager->disconnect();

    delete _scene;

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    stream >> _scene;
    ui->treeView->setModel(_scene);
    ui->viewport->setScene(_scene);

    //TODO encapsulate this ...each attribute manager must be connected to each tree view!
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, [this](){
       QList<Object*> selection;
       for (QModelIndex i : ui->treeView->selectionModel()->selection().indexes())
           selection.append(ui->treeView->model()->getObject(i));
       ui->attributeManager->setSelection(selection);
    });
    //connect(_scene, SIGNAL(changed()), ui->treeView, SLOT(update()));

    file.close();

    createToolMenu();
}
void MainWindow::createToolMenu()
{
    TOOL_CREATOR_MAP_TYPE* _map = Tool::creatorMap();

    if (!_toolMenu) {
        _toolMenu = new QMenu("Tools", this);
    } else {
        for (QAction* a : _toolMenu->actions()) {
            _toolMenu->removeAction(a);
            delete a;
        }
        delete _toolMenuActionGroup;
    }


    QList<QString> toolClassnames = _map->keys();
    qSort(toolClassnames);

    QActionGroup* _toolMenuActionGroup = new QActionGroup(_toolMenu);
    QList<QAction*> actions;
    for (QString key : toolClassnames) {
        Tool* t = Tool::createInstance(key);
        QAction* action = new QAction(_toolMenu);
        action->setText(t->name());
        action->setToolTip(t->toolTip());
        action->setIcon(t->icon());
        action->setCheckable(true);
        action->setActionGroup(_toolMenuActionGroup);
        connect(action, &QAction::toggled, [this, key](bool on) {
            if (!on) return;
            if (!_scene) return;
            _scene->setTool(Tool::createInstance(key));
        });
        delete t;
        actions << action;
    }

    connect(_scene, &Scene::destroyed, [_toolMenuActionGroup]() {
        for (QAction* a : _toolMenuActionGroup->actions()) {
            a->setChecked(false);
        }
    });
    _toolMenu->addActions(actions);
}
