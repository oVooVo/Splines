#include "transformationattributetest.h"

REGISTER_DEFN_UNITTESTYPE(TransformationAttributeTest);

TransformationAttributeTest::TransformationAttributeTest(QObject *parent) : UnitTest(parent)
{
}

void TransformationAttributeTest::initTestCase()
{
    transformationAttribute = new TransformationAttribute();
}

void TransformationAttributeTest::cleanupTestCase()
{
    delete transformationAttribute;
}

void TransformationAttributeTest::setValueTest()
{
    const int tests = 5;
    qreal values[tests][5] = {
        { 0, 0, 1, 1, 0 },
        { 2, 2, 1, 1, 5 },
        { 4, 2, 1, 1, M_PI },
        { 0, 2, 2, 2, 0 },
        { -12, 33, -1, 2, 12}
    };

    for (int i = 0; i < tests; i++) {
        QTransform t;
        t.translate(values[i][0], values[i][1]);
        t.scale(values[i][2], values[i][3]);
        t.rotate(values[i][4]);

        transformationAttribute->setValue(t);
        QTransform t_ = transformationAttribute->value();
        QCOMPARE(t, t_);
    }


}

void TransformationAttributeTest::valueTest()
{
}
