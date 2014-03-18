#ifndef UNITTEST_H
#define UNITTEST_H

#include <QObject>
#include <QMap>

class UnitTest;
#define UNITTEST_CREATOR_MAP_TYPE QMap<QString, UnitTest* (*)()>
template<typename T> UnitTest *createUnitTest() { return new T(); }

class UnitTest : public QObject
{
public:
    UnitTest(QObject* parent = 0);

protected:
    static UNITTEST_CREATOR_MAP_TYPE *_creatorMap;
    static UnitTest *createInstance();
    friend class UnitTester;
};

template<typename T>
struct UnitTestRegister : UnitTest
{
    UnitTestRegister(QString className) : UnitTest()
    {
        if (!_creatorMap)
            _creatorMap = new UNITTEST_CREATOR_MAP_TYPE();
        _creatorMap->insert(className, &createUnitTest<T>);
    }
};

#define REGISTER_DECL_UNITTESTTYPE(CLASSNAME) \
    static UnitTestRegister<CLASSNAME> reg

#define REGISTER_DEFN_UNITTESTYPE(CLASSNAME) \
    UnitTestRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

#endif // UNITTEST_H
