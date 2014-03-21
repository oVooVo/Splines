#ifndef REGISTERDEFINES_H
#define REGISTERDEFINES_H

#include <QStringList>
#include <QMap>


/**
  Defines to make use of Attribute system easier.

    Macro (1) before Q_OBJECT Macro
    Macro (2) after class definition
    Macro (4) in class declaration
    Macro (5) before class definition

    Example:
    There must be a Base class from that all registered Objects will derive.
    Further there is for example one Class Foo that derives Base and is registered.
    // [...] means you can paste arbitrary c++ code.

    // base.h ----------------------------------------
    #include <QObject>
    class Base : public QObject
    {
        Q_OBJECT
        DECL_MEMBER(Base)

    public:
        Tool();

        // [...]

    };
    REGISTERER(Base)
    //------------------------------------------------

    //base.cpp ---------------------------------------
    INIT_CREATOR_MAP(Base);

    Base::Base()
    {
        // [...]
    }
    // [...]
    //------------------------------------------------

    //foo.h ------------------------------------------
    #include "base.h"
    class Foo : public Base
    {
        Q_OBJECT
        REGISTER_DECL_TYPE(Base, Foo);
    public:
        NewPointTool();

        // [...]
    };
    //------------------------------------------------

    //foo.cpp ----------------------------------------
    REGISTER_DEFN_TYPE(Base, Foo);

    Foo::Foo()
    {
        //...
    }

    // [...]
    //------------------------------------------------

  */


// (1)
#define DECL_MEMBER(CLASSNAME)                                                          \
    private:                                                                            \
        static CREATOR_MAP_TYPE(CLASSNAME) *_creatorMap;                                \
    public:                                                                             \
        static CLASSNAME *createInstance(QString classname)                             \
        {                                                                               \
            if (!_creatorMap)                                                           \
            {                                                                           \
                _creatorMap = new CREATOR_MAP_TYPE(CLASSNAME)();                        \
            }                                                                           \
            CREATOR_MAP_TYPE(CLASSNAME)::iterator it = _creatorMap->find(classname);    \
            if (it == _creatorMap->end())                                               \
                return 0;                                                               \
            return (it.value())();                                                      \
        }                                                                               \
        static QStringList types() { return _creatorMap->keys(); }                      \
        template<typename T> friend class CLASSNAME##Register;                         //

// (2)
#define REGISTERER(CLASSNAME)                                                    \
class CLASSNAME;                                                                 \
template<typename T> CLASSNAME *create##CLASSNAME() { return new T(); }          \
template<typename T>                                                             \
struct CLASSNAME##Register                                                       \
{                                                                                \
    CLASSNAME##Register(QString classname)                                       \
    {                                                                            \
        if (!CLASSNAME::_creatorMap)                                             \
            CLASSNAME::_creatorMap = new CREATOR_MAP_TYPE(CLASSNAME);            \
        CLASSNAME::_creatorMap->insert(classname, &create##CLASSNAME<T>);        \
    }                                                                            \
};                                                                              //

// (3)
#define REGISTER_DECL_TYPE(CLASSNAME_A, CLASSNAME_B)    \
    private:                                            \
    static CLASSNAME_A##Register<CLASSNAME_B> reg      //

// (4)
#define REGISTER_DEFN_TYPE(CLASSNAME_A, CLASSNAME_B)                    \
    CLASSNAME_A##Register<CLASSNAME_B> CLASSNAME_B::reg(#CLASSNAME_B)  //


// helper
#define CREATOR_MAP_TYPE(CLASSNAME) QMap<QString, CLASSNAME* (*)()>
#define INIT_CREATOR_MAP(CLASSNAME) CREATOR_MAP_TYPE(CLASSNAME) *CLASSNAME::_creatorMap = 0





#endif // REGISTERDEFINES_H
