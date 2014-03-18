#include "mainwindow.h"
#include <QApplication>
#include "viewport.h"
#include "unittester.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UnitTester *tester = new UnitTester();
    delete tester;

    MainWindow w;
    w.show();

    return a.exec();
}
