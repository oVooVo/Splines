#include "mainwindow.h"
#include <QApplication>
#include "viewport.h"
#include "Tests/unittester.h"

//#define TEST


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef TEST
    UnitTester *tester = new UnitTester();
    delete tester;
    return 0;
#else
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
