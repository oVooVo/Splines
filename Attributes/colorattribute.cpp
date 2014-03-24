#include "colorattribute.h"

REGISTER_DEFN_TYPE(Attribute, ColorAttribute);

ColorAttribute::ColorAttribute(QString label, QColor value) : Attribute(label)
{
    _color = value;
}


QColor ColorAttribute::color() const
{
    return _color;
}

QString ColorAttribute::toString() const
{
    QString s;
    s.append(QString("%1%2%3%4")
             .arg(color().red(),   2, 16, QChar('0'))
             .arg(color().green(), 2, 16, QChar('0'))
             .arg(color().blue(),  2, 16, QChar('0'))
             .arg(color().alpha(), 2, 16, QChar('0')));
    return s;
}

void ColorAttribute::fromString(QString string)
{
    auto getHex = [](QString h, int def) {
        bool ok;
        int i = h.toInt(&ok, 16);
        return ok ? i : def;
    };

    setColor(QColor(getHex(string.mid(0, 2), 0), getHex(string.mid(2, 2), 0  ),
                    getHex(string.mid(4, 2), 0), getHex(string.mid(6, 2), 255)));
}

void ColorAttribute::setColor(QColor color)
{
    if (_color == color) return;

    _color = color;
    emit changed();
}
