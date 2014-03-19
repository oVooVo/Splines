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
    setScene(new Scene());

    connect(ui->actionSpeichern, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSpeichern_unter, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->action_ffnen, SIGNAL(triggered()), this, SLOT(load()));


    connect(ui->actionNewSpline, &QAction::triggered, [this]() { _scene->addObject(new Spline()); });


    menuBar()->addMenu(createToolMenu());
    menuBar()->addMenu(createManagerMenu());
    menuBar()->addMenu(createNewObjectsMenu());

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
        return;
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

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    Scene* scene;
    stream >> scene;
    setScene(scene);

}

void MainWindow::setScene(Scene *scene)
{
    ui->viewport->setScene(scene); //TODO: viewport should be a manager too! (but no QDockWidget...)
    for (Manager* manager : _managers) {
        manager->setScene(scene);
    }

    if (_scene)
        delete _scene;  //all connections that target _scene were destroyed :)

    _scene = scene;

}

void MainWindow::addManager(Manager *manager)
{
    manager->setScene(_scene);
    _managers.append(manager);
}

QMenu* MainWindow::createToolMenu()
{
    auto connectAction = [this](const QString& classname, const QAction* action) {
        connect(action, &QAction::toggled, [this, classname](bool on) {
            if (!on) return;
            if (!_scene) return;
            _scene->setTool(Tool::createInstance(classname));
        });
        return action;
    };

    return createMenu<Tool>(connectAction, "Tool Menu");
}

QMenu* MainWindow::createManagerMenu()
{
    auto connectAction = [this](const QString& classname, const QAction* action) {
        connect(action, &QAction::triggered, [this, classname]() {
            Manager* manager = Manager::createInstance(classname);
            addManager(manager);
            manager->setParent(this);
            manager->setFloating(true);
            manager->show();
        });
    };

    return createMenu<Manager>(connectAction, "Manager Menu");
}

QMenu* MainWindow::createNewObjectsMenu()
{
    auto connectAction = [this](const QString& classname, const QAction* action) {
        connect(action, &QAction::triggered, [this, classname]() {
            if (_scene) {
                _scene->addObject(Object::createInstance(classname));
            }
        });
    };

    return createMenu<Object>(connectAction, "Add Object");
}

template<typename T> QMenu* MainWindow::createMenu(CONNECT_ACTION_TYPE connectAction, QString name)
{
    QMenu* menu = new QMenu(name, this);

    QStringList classnames = T::types();
    qSort(classnames);

    QActionGroup* group = new QActionGroup(menu);
    QList<QAction*> actions;
    for (QString classname : classnames) {
        T* t = T::createInstance(classname);
        if (t->makeAction()) {
            QAction* action = new QAction(menu);
            connectAction(classname, action);
            action->setParent(menu);
            action->setActionGroup(group);
            action->setText(t->actionText());
            action->setToolTip(t->toolTip());
            action->setIcon(t->icon());
            action->setCheckable(t->isCheckable());
            if (action->isCheckable()) {
                connect(_scene, &Scene::destroyed, [action]() {
                    action->setChecked(false);
                });
            }
            actions << action;
        }
        delete t;
    }
    menu->addActions(actions);
    return menu;
}






























