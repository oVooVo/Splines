#include "typeattribute.h"

REGISTER_DEFN_ATTRIBUTETYPE(TypeAttribute);

TypeAttribute::TypeAttribute(QString label, QStringList types)
{
    _types = types;
    _label = label;
}

TypeAttribute::TypeAttribute(QDataStream &stream) : Attribute(stream)
{
    stream >> _types >> _label >> _currentIndex;
}

void TypeAttribute::serialize(QDataStream &out) const
{
    Attribute::serialize(out);
    out << _types << _label << _currentIndex;
}

QString TypeAttribute::currentText() const
{
    return _types[currentIndex()];
}

void TypeAttribute::setCurrentIndex(int ind)
{
    if (_currentIndex == ind) return;

    Q_ASSERT_X(ind < _types.size() && ind >= 0, "TypeAttribute::setCurrentIndex", "invalid index");
    _currentIndex = ind;
    emit changed();
}
