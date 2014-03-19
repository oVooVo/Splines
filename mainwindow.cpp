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
    delete _scene;

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    stream >> _scene;

    createToolMenu();
}

void MainWindow::setScene(Scene *scene)
{
    if (_scene)
        delete _scene;  //all connections that target _scene were destroyed :)

    _scene = scene;

    ui->viewport->setScene(_scene); //TODO: viewport should be a manager too! (but no QDockWidget...)
    for (Manager* manager : _managers) {
        manager->setScene(_scene);
    }
}

void MainWindow::addManager(Manager *manager)
{
    _managers.append(manager);
}

QMenu* MainWindow::createToolMenu()
{
    std::function<QAction*(Tool*, QString)> makeAction = [this](Tool* t, QString key) -> QAction* {
        QAction* action = new QAction(0);
        action->setCheckable(true);
        action->setText(t->name());
        action->setToolTip(t->toolTip());
        action->setIcon(t->icon());
        connect(action, &QAction::toggled, [this, key](bool on) {
            if (!on) return;
            if (!_scene) return;
            _scene->setTool(Tool::createInstance(key));
        });
        connect(_scene, &Scene::destroyed, [action]() {
           action->setChecked(false);
        });
        return action;
    };

    return createMenu<Tool>(makeAction, "Tool Menu");
}

QMenu* MainWindow::createManagerMenu()
{
    std::function<QAction*(Manager*, QString)> makeAction = [this](Manager* t, QString key) -> QAction* {
        QAction* action = new QAction(0);
        action->setText(t->name());
        action->setToolTip(t->toolTip());
        action->setIcon(t->icon());
        connect(action, &QAction::triggered, [this, key]() {
            Manager* manager = Manager::createInstance(key);
            addManager(manager);
            manager->show();
        });
        return action;
    };

    return createMenu<Manager>(makeAction, "Manager Menu");
}

template<typename T> QMenu* MainWindow::createMenu(std::function<QAction*(T*, QString)> makeAction, QString name)
{
    QMenu* menu = new QMenu(name, this);

    QStringList keys = T::types();
    qSort(keys);

    QActionGroup* group = new QActionGroup(menu);
    QList<QAction*> actions;
    for (QString key : keys) {
        T* t = T::createInstance(key);
        QAction* action = makeAction(t, key);
        delete t;
        action->setParent(menu);
        action->setActionGroup(group);
        actions << action;
    }
    menu->addActions(actions);
    return menu;
}






























