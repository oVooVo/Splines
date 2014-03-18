#ifndef TRANSFORMATIONATTRIBUTETEST_H
#define TRANSFORMATIONATTRIBUTETEST_H

#include "Tests/unittest.h"
#include <QtTest/QtTest>
#include "transformationattribute.h"


class TransformationAttributeTest : public UnitTest
{
    Q_OBJECT
public:
    TransformationAttributeTest(QObject* parent = 0);

private slots:
    void initTestCase();
    void cleanupTestCase();
    void setValueTest();
    void valueTest();

private:
    TransformationAttribute* transformationAttribute;
    REGISTER_DECL_UNITTESTTYPE(TransformationAttributeTest);

};

#endif // TRANSFORMATIONATTRIBUTETEST_H
