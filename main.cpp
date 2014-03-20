#include "mainwindow.h"
#include <QApplication>
#include "viewport.h"
#include "Tests/unittester.h"
#include <QString>
#include <QRegExp>
#include <QDebug>

//#define TEST


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("Oyolo");
    QApplication::setApplicationDisplayName("Oyolo");
    QApplication::setOrganizationName("oyolo");

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
