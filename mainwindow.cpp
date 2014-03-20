#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "Tools/tool.h"
#include <Managers/objectmanager.h>
#include <Managers/attributemanager.h>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    installEventFilter(this);
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionNewScene, SIGNAL(triggered()), this, SLOT(newScene()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    menuBar()->addMenu(createToolMenu());
    menuBar()->addMenu(createManagerMenu());
    menuBar()->addMenu(createNewObjectsMenu());
    updateWindowTitle();

    newScene();

    Manager* m;
    m = new ObjectManager(this);
    addManager(m, false);
    addDockWidget(Qt::RightDockWidgetArea, m);
    m->setScene(_scene);

    m = new AttributeManager(this);
    addManager(m, false);
    addDockWidget(Qt::RightDockWidgetArea, m);
    m->setScene(_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::save()
{
    if (_filepath.isEmpty() && !saveAs()) {
        return false;
    }

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);

    if (!file.isWritable())
        return false;

    QDataStream stream(&file);
    stream << _scene;
    file.close();

    _isSaved = true;
    updateWindowTitle();
    return true;
}

QString MainWindow::fileDialogDirectory() const
{
    return _filepath.isEmpty() ? QDir::home().absolutePath() : _filepath;
}

bool MainWindow::saveAs()
{
    _filepath = QFileDialog::getSaveFileName(this, "Save Project", fileDialogDirectory());
    if (!_filepath.isEmpty()) {
        return save();
    } else {
        return false;
    }
}

bool MainWindow::newScene()
{
    if (!canDiscard()) return false;

    setScene(new Scene());

    return true;
}

bool MainWindow::load()
{
    if (!canDiscard()) return false;

    _filepath = QFileDialog::getOpenFileName(this, "Open Project", fileDialogDirectory());
    if (_filepath.isEmpty()) return false;

    QFile file(_filepath);
    file.open(QIODevice::ReadWrite);

    if (!file.isReadable())
        return false;

    QDataStream stream(&file);
    Scene* scene;
    stream >> scene;

    if (scene) {
        setScene(scene);
        return true;
    } else {
        QMessageBox::warning(this,
                             "Error",
                             QString("Failed loading file %1").arg(_filepath),
                             QMessageBox::Ok, QMessageBox::Ok);
        return false;
    }

}

void MainWindow::setScene(Scene *scene)
{
    ui->viewport->setScene(scene); //TODO: viewport should be a manager too! (but no QDockWidget...)

    if (_scene) {
        for (Manager* manager : _scene->managers()) {
            manager->setScene(scene);
        }
        delete _scene;  //all connections that target _scene were destroyed :)
    }

    _scene = scene;

    if (_scene) {
        connect(_scene, &Scene::changed, [this](){
            if (!_isSaved) return;

            _isSaved = false;
            updateWindowTitle();
        });

        connect(_scene, &Scene::destroyed, [this]() {
            for (QAction* a : _checkableActions)
                a->setChecked(false);
        });

        _isSaved = true;
        updateWindowTitle();
    }
}

void MainWindow::addManager(Manager *manager, bool floating)
{
    if (_scene) {
        manager->setScene(_scene);
        manager->setParent(this);
        manager->setFloating(floating);
        manager->show();
    } else {
        delete manager;
    }
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
        Action* t = T::createInstance(classname);
        if (t->makeAction()) {
            QAction* action = new QAction(menu);
            connectAction(classname, action);
            action->setParent(menu);
            if (!t->isCommand()) {
                action->setActionGroup(group);
                action->setCheckable(true);
            }
            action->setText(t->actionText());
            action->setToolTip(t->toolTip());
            action->setIcon(t->icon());
            if (action->isCheckable()) {
                _checkableActions << action;
            }
            actions << action;
        }
        delete t;
    }
    menu->addActions(actions);
    return menu;
}

void MainWindow::updateWindowTitle()
{
    QString filename = tr("New File");

    if (!_filepath.isEmpty()) {
        QFileInfo fileInfo = QFileInfo(_filepath);
        filename = fileInfo.fileName();
    }
    if (!_isSaved)
        filename.append(" *");
    setWindowTitle(filename);
}

bool MainWindow::canDiscard()
{
    if (_isSaved) return true;

    QMessageBox::StandardButton ans = QMessageBox::question(this, tr("Discard?"), tr("There are unsaved changes. Do you want to save?"),
                                                            QMessageBox::Save | QMessageBox::Abort | QMessageBox::Discard,
                                                            QMessageBox::Save);
    switch (ans) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Abort:
        return false;
    case QMessageBox::Discard:
        return true;
    default:
        return true;
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (canDiscard()) {
        e->accept();
    } else {
        e->ignore();
    }
}
















