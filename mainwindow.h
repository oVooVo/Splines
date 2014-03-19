#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"
#include "viewport.h"
#include "Objects/spline.h"
#include <QActionGroup>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void addSpline();

    void save();
    void saveAs();
    void load();

private:
    Ui::MainWindow *ui;
    Scene* _scene;
    QString _filepath;
    QString fileDialogDirectory() const;
    void createToolMenu();

    QMenu* _toolMenu = 0;
    QActionGroup* _toolMenuActionGroup = 0;

};

#endif // MAINWINDOW_H
