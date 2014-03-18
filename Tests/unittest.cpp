#include "unittest.h"

UNITTEST_CREATOR_MAP_TYPE *UnitTest::_creatorMap = 0;


UnitTest::UnitTest(QObject *parent) : QObject(parent)
{
}
