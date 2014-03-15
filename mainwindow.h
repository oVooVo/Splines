#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"
#include "viewport.h"
#include "Objects/spline.h"


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

private:
    Ui::MainWindow *ui;
    Scene* _scene;
};

#endif // MAINWINDOW_H
