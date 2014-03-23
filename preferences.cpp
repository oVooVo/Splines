#include "preferences.h"
#include <QSettings>
#include <QDebug>

QMap<QString, QColor> Preferences::colors;
QMap<QString, double> Preferences::doubles;

void Preferences::init()
{
    initColors();
    initDoubles();
}

void Preferences::initColors()
{
    colors.clear();
    colors.insert("Point.active.selected",
                  QColor(232, 121, 0));
    colors.insert("Point.active.deselected",
                  QColor(80, 60, 45));
    colors.insert("Point.inactive",
                  QColor(100, 90, 80));
    colors.insert("Spline.active.start",
                  QColor(0, 255, 0));
    colors.insert("Spline.active.end",
                  QColor(0, 255, 255));
    colors.insert("Spline.inactive",
                  QColor(128, 128, 128));
    colors.insert("Background",
                  QColor(255, 255, 255));
}

void Preferences::initDoubles()
{
    doubles.clear();
    doubles.insert("Grabber.Tolerance", 4);
}

QColor fromHex(QString hex)
{
    auto getHex = [](QString h, int def) {
        bool ok;
        int i = h.toInt(&ok, 16);
        return ok ? i : def;
    };

    return QColor(getHex(hex.mid(0, 2), 0), getHex(hex.mid(2, 2), 0  ),
                  getHex(hex.mid(4, 2), 0), getHex(hex.mid(6, 2), 255));
}

QString toHex(QColor color)
{
    QString s;
    s.append(QString("%1%2%3%4")
             .arg(color.red(),   2, 16, QChar('0'))
             .arg(color.green(), 2, 16, QChar('0'))
             .arg(color.blue(),  2, 16, QChar('0'))
             .arg(color.alpha(), 2, 16, QChar('0')));
    return s;
}


void Preferences::readSettings()
{
    QSettings s;
    for (QString key : colors.keys()) {
        colors.insert(key, fromHex(s.value(key, toHex(colors[key])).toString()));
    }
    for (QString key : doubles.keys()) {
        doubles.insert(key, s.value(key, doubles[key]).toDouble());
    }
}

void Preferences::writeSettings()
{
    QSettings s;
    for (QString key : colors.keys()) {
        s.setValue(key, toHex(colors[key]));
    }
    for (QString key : doubles.keys()) {
        s.setValue(key, doubles[key]);
    }
}
