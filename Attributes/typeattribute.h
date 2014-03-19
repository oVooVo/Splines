#ifndef TYPEATTRIBUTE_H
#define TYPEATTRIBUTE_H

#include "attribute.h"
#include <QStringList>

class TypeAttribute : public Attribute
{
    Q_OBJECT
public:
    TypeAttribute(QString label, QStringList types);
    TypeAttribute(QDataStream& stream);
    void serialize(QDataStream &out) const;

    int currentIndex() const { return _currentIndex; }
    QString currentText() const;
    QString label() const { return _label; }
    QStringList types() const { return _types; }

public slots:
    void setCurrentIndex(int ind);

private:
    qint64 _currentIndex = 0;
    QStringList _types;
    QString _label;
    REGISTER_DECL_ATTRIBUTETYPE(TypeAttribute);
};

#endif // TYPEATTRIBUTE_H
