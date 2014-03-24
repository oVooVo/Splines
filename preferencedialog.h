#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>
#include "preferences.h"
#include <QTabWidget>
#include <QGroupBox>

class PreferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceDialog(QWidget *parent = 0);
    ~PreferenceDialog();
    void createUi();

private slots:
    void on_accept();

private:
    static QStringList getTabNames();
    QWidget* createTabWidget(QString name, QWidget *parent = 0);
    QGroupBox* createGroupBox(QString pref, QWidget* parent = 0);
    QTabWidget* _tabWidget;
};

#endif // PREFERENCEDIALOG_H
