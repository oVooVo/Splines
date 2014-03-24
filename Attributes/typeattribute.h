#ifndef TYPEATTRIBUTE_H
#define TYPEATTRIBUTE_H

#include "attribute.h"

class TypeAttribute : public Attribute
{
    Q_OBJECT
public:
    TypeAttribute(QString label = "Label: ", QStringList types = QStringList());

    int currentIndex() const { return _currentIndex; }
    QString currentText() const;
    QStringList types() const { return _types; }
    QString toString() const;
    void fromString(QString string);

public slots:
    void setCurrentIndex(int ind);

protected:
    void registerAttributeData(QDataStream &stream, Direction direction);


private:
    qint64 _currentIndex = 0;
    QStringList _types;
    REGISTER_DECL_TYPE(Attribute, TypeAttribute);
};

#endif // TYPEATTRIBUTE_H
