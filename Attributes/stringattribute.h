#ifndef STRINGATTRIBUTE_H
#define STRINGATTRIBUTE_H

#include "attribute.h"


class StringAttribute : public Attribute
{
    Q_OBJECT
public:
    StringAttribute(QString label = "Label: ", QString string = "");
    QString string() const { return _string; }
    void fromString(QString string);
    QString toString() const;

public slots:
    void setString(const QString &string);

protected:
    void registerAttributeData(QDataStream &stream, Direction direction);

private:
    QString _string;
    REGISTER_DECL_TYPE(Attribute, StringAttribute);
};

#endif // STRINGATTRIBUTE_H
