#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QMap>
#include <QColor>
#include "gradient.h"
#include "Attributes/attribute.h"

class Preferences
{
private:
    Preferences() {}

public:
    static void writeSettings();
    static void readSettings();
    static void init();
    template<class T> static T* value(QString key) { return (T*) _attributes[key]; }
    static Attribute* attribute(QString key) { return _attributes[key]; }
    static QStringList keys() { return _attributes.keys(); }


private:
    static QMap<QString, Attribute*> _attributes;

};

#endif // PREFERENCES_H
