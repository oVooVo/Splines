#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QLineEdit>

class TestObject : public QLineEdit
{
    Q_OBJECT
public:
    explicit TestObject(QWidget *parent = 0);
    ~TestObject();
    void setText(const QString & text);

signals:

public slots:

};

#endif // TESTOBJECT_H
