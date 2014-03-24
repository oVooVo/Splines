#include "preferences.h"
#include <QSettings>
#include <QDebug>
#include "Attributes/colorattribute.h"
#include "Attributes/doubleattribute.h"

QMap<QString, Attribute*> Preferences::_attributes;


void Preferences::init()
{
    Q_ASSERT(_attributes.isEmpty());

    // PreferenceDialog creates a tab widget out of the _attributes.
    // _attribute's keys have form Tab.GroupBox.Name where name is replaced with the attributes label.

    _attributes.insert("colors.point.active.selected",
                       new ColorAttribute("Selected: " , QColor(232, 121, 0)));
    _attributes.insert("colors.point.active.deselected",
                       new ColorAttribute("Deselected: ", QColor(80, 60, 45)));
    _attributes.insert("colors.point.inactive",
                       new ColorAttribute("Inactive: ", QColor(100, 90, 80)));
    _attributes.insert("colors.spline.active.start",
                       new ColorAttribute("Start: ", QColor(0, 255, 0)));
    _attributes.insert("colors.spline.active.end",
                       new ColorAttribute("End: ", QColor(0, 255, 255)));
    _attributes.insert("colors.spline.inactive",
                       new ColorAttribute("Inactive: ", QColor(128, 128, 128)));
    _attributes.insert("colors.background",
                       new ColorAttribute("Background: ", QColor(255, 255, 255)));
    _attributes.insert("grabber.tolerance.tolerance",
                       new DoubleAttribute("Tolerance:", 4.0));
}

void Preferences::readSettings()
{
    QSettings s;
    for (QString key : _attributes.keys()) {
        Attribute* a = _attributes[key];
        QString code = s.value(key, QVariant()).toString();
        if (!code.isEmpty()) {
            a->fromString(code);
        }
    }
}

void Preferences::writeSettings()
{
    QSettings s;
    for (QString key : _attributes.keys()) {
        s.setValue(key, _attributes[key]->toString());
    }
}
