#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QMap>
#include <QColor>
#include "gradient.h"

class Preferences
{
private:
    Preferences() {}

public:
    static QMap<QString, QColor> colors;
    static QMap<QString, double> doubles;
    static void writeSettings();
    static void readSettings();
    static void init();

private:
    static void initColors();
    static void initDoubles();
};

#endif // PREFERENCES_H
