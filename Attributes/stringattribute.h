#ifndef STRINGATTRIBUTE_H
#define STRINGATTRIBUTE_H

#include "attribute.h"


class StringAttribute : public Attribute
{
    Q_OBJECT
public:
    StringAttribute(QString label, QString string = "");
    StringAttribute(QDataStream &stream);
    QString string() const { return _string; }
    QString label() const { return _label; }

public slots:
    void setString(const QString &string);
    void setLabel(const QString &label);

protected:
    void serialize(QDataStream &out) const;


private:
    QString _string = "";
    QString _label = "Label:";
    REGISTER_DECL_ATTRIBUTETYPE(StringAttribute);
};

#endif // STRINGATTRIBUTE_H
