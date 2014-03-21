#include "typeattribute.h"

REGISTER_DEFN_TYPE(Attribute, TypeAttribute);

TypeAttribute::TypeAttribute(QString label, QStringList types) : Attribute(label)
{
    _types = types;
}

void TypeAttribute::registerAttributeData(QDataStream &stream, Direction direction)
{
    REGISTER_DATA(_types)
    REGISTER_DATA(_currentIndex)
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
