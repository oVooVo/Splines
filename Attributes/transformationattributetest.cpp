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
    const int tests = 1;
    qreal values[tests][5] = {
        { 12, -100, 1, 1, 0 }
    };

    for (int i = 0; i < tests; i++) {
        QTransform t;
        t.translate(values[i][0], values[i][1]);
        t.scale(values[i][2], values[i][3]);
        t.rotate(values[i][4]);

        qDebug() << "test #" << i;
        transformationAttribute->setValue(t);
        QCOMPARE(transformationAttribute->x(), values[i][0]);
        QCOMPARE(transformationAttribute->y(), values[i][1]);
        QCOMPARE(transformationAttribute->sx(), values[i][2]);
        QCOMPARE(transformationAttribute->sy(), values[i][3]);
        QCOMPARE(transformationAttribute->r(), values[i][4]);

    }


}

void TransformationAttributeTest::valueTest()
{
}
