#include "typeattribute.h"
#include <QDebug>

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

QString TypeAttribute::toString() const
{
    return QString("%1").arg(currentIndex());
}

void TypeAttribute::fromString(QString string)
{
    bool ok;
    setCurrentIndex(string.toInt(&ok));
    if (!ok) {
        qWarning() << "cannot parse " << string;
    }
}
