#include "unittester.h"
#include "Attributes/transformationattributetest.h"

#include <QtTest/QtTest>
#include <QStringList>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#define CLEAR() std::system("CLS")
#else
#define CLEAR() std::system("clear")
#endif

template<typename T> QObject *test() { return new T(); }

UnitTester::UnitTester()
{
    QVector<int> failedTests;
    QString data = "";
    for(int i = 0; i < UnitTest::_creatorMap->size(); i++) {
        QObject* testCase = UnitTest::_creatorMap->values()[i]();
        delete testCase; // To ensure the destructor works good.
        testCase = UnitTest::_creatorMap->values()[i]();
        if(QTest::qExec(testCase) == 0) {
            data = data + "********* Passed testing of " + testCase->metaObject()->className() + " *********\n";
        } else {
            failedTests += i;
        }
        delete testCase;
    }
    foreach(int i, failedTests) {
        QObject* testCase = UnitTest::_creatorMap->values()[i]();
        QTest::qExec(testCase, QStringList() << "BEEF" << "-o" << "temp");
        QFile f("temp");
        f.open(QIODevice::ReadOnly);
        QTextStream ts(f.readAll());
        f.close();
        data += ts.readAll();
        QFile::remove("temp");
        delete testCase;
    }
    CLEAR();
    qDebug() << data;
}
