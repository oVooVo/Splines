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
#include "preferences.h"
#include "preferencedialog.h"
#include "Managers/statusbar.h"

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
    connect(ui->actionPreferences, &QAction::triggered, [this](){
        PreferenceDialog dialog(this);
        dialog.exec();
    });

    menuBar()->addMenu(createToolMenu());
    menuBar()->addMenu(createManagerMenu());
    menuBar()->addMenu(createNewObjectsMenu());
    updateWindowTitle();

    _undoHandler = new UndoHandler(this);
    connect(_undoHandler, SIGNAL(canRedo(bool)), ui->actionRedo, SLOT(setEnabled(bool)));
    connect(_undoHandler, SIGNAL(canUndo(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->actionRedo, SIGNAL(triggered()), _undoHandler, SLOT(redo()));
    connect(ui->actionUndo, SIGNAL(triggered()), _undoHandler, SLOT(undo()));
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    connect(_undoHandler, &UndoHandler::currentSceneChanged, [this](Scene* scene) {
        setScene(scene);
        _isSaved = false;
    });


    newScene();

    DockableManager* m;
    m = new ObjectManager(this);
    addManager(m);
    addDockWidget(Qt::RightDockWidgetArea, m);
    m->setFloating(false);
    m->setScene(_scene);

    m = new AttributeManager(this);
    addManager(m);
    addDockWidget(Qt::RightDockWidgetArea, m);
    m->setFloating(false);
    m->setScene(_scene);

    StatusBar* statusBar = new StatusBar(this);
    addManager(statusBar);
    statusBar->setScene(_scene);
    setStatusBar(statusBar);

    addManager(ui->viewport);

    Preferences::init();
    Preferences::readSettings();


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

    Scene* newScene = new Scene();
    setScene(newScene);
    _undoHandler->setScene(newScene);
    _filepath = "";

    updateWindowTitle();

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
        _undoHandler->setScene(scene);
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
    QString toolName;
    if (_scene) {
        if (_scene->tool())
            toolName = _scene->tool()->metaObject()->className();

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

//        connect(_scene, &Scene::destroyed, [this]() {
//            for (QAction* a : _checkableActions)
//                a->setChecked(false);
//        });

        if (!toolName.isEmpty())
            _scene->setTool(Tool::createInstance(toolName));
        _isSaved = true;
        updateWindowTitle();
    }
}

void MainWindow::addManager(Manager *manager)
{
    if (_scene) {
        manager->setScene(_scene);
    } else {
        delete manager;
    }
}

QMenu* MainWindow::createToolMenu()
{
    auto connectAction = [this](const QString& classname, const QAction* action) {
        if (action->isCheckable()) {
            connect(action, &QAction::toggled, [this, classname](bool on) {
                if (!on) return;
                if (!_scene) return;
                _scene->setTool(Tool::createInstance(classname));
            });
        } else {
            connect(action, &QAction::triggered, [this, classname]() {
                if (!_scene) return;
                _scene->setTool(Tool::createInstance(classname));
            });
        }
        return action;
    };

    return createMenu<Tool>(connectAction, "Tool Menu");
}

QMenu* MainWindow::createManagerMenu()
{
    auto connectAction = [this](const QString& classname, const QAction* action) {
        connect(action, &QAction::triggered, [this, classname]() {
            DockableManager* manager = DockableManager::createInstance(classname);
            addManager(manager);
            manager->setParent(this);
            manager->setFloating(true);
            manager->show();
        });
    };

    return createMenu<DockableManager>(connectAction, "Manager Menu");
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
















