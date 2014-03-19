#include "testobject.h"
#include <QDebug>

TestObject::TestObject(QWidget *parent) :
    QLineEdit(parent)
{
}

TestObject::~TestObject()
{
    qDebug() << "delete TestObject";
}

void TestObject::setText(const QString &text)
{
    qDebug() << "set Text";
    QLineEdit::setText(text);
}
