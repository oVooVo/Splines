#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>
#include "preferences.h"

namespace Ui {
class PreferenceDialog;
}

class PreferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceDialog(QWidget *parent = 0);
    ~PreferenceDialog();

private:
    Ui::PreferenceDialog *ui;

private slots:
    void on_accept();
};

#endif // PREFERENCEDIALOG_H
