#ifndef POINTEDITDIALOG_H
#define POINTEDITDIALOG_H

#include <QDialog>
#include "point.h"

namespace Ui {
class PointEditDialog;
}

class PointEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointEditDialog(Point* p, bool tangents, QWidget *parent = 0);
    ~PointEditDialog();

    QPointF point() const;
    QPointF left() const;
    QPointF right() const;
    bool tangents() const { return _tangents; }

private:
    Ui::PointEditDialog *ui;
    bool _tangents;
    Point* _point;

private slots:
    void on_accept();

public:
    bool static exec_static(Point* p, bool tangents, QWidget *parents = 0);

};

#endif // POINTEDITDIALOG_H
