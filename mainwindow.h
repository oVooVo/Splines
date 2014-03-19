#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"
#include "viewport.h"
#include "Objects/spline.h"
#include <QActionGroup>
#include "Managers/manager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setScene(Scene* scene);


public slots:
    void addSpline();

    void save();
    void saveAs();
    void load();

private:
    Ui::MainWindow *ui;
    Scene* _scene = 0;
    QString _filepath;
    QString fileDialogDirectory() const;

    void addManager(Manager* manager);
    QList<Manager*> _managers;

    /**
     * @brief createMenu creates a Menu out of Registered classes
     * @return
     */
#define CONNECT_ACTION_TYPE std::function<void(const QString&, const QAction*)>
    template<typename T> QMenu* createMenu(CONNECT_ACTION_TYPE connectAction, QString name);


    QMenu* createToolMenu();
    QMenu* _toolMenu = 0;
    QMenu* createManagerMenu();
    QMenu* _managerMenu = 0;
    QMenu* createNewObjectsMenu();
    QMenu* _newObjectsMenu = 0;

};

#endif // MAINWINDOW_H

