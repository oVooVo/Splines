#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include "manager.h"
#include <QLabel>

class StatusBar : public QStatusBar, public Manager
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = 0);

    void sceneChanged()     { updateText(); }
    void selectionChanged() { updateText(); }

private:
    void updateText();
    QLabel* _messageLabel;

};

#endif // STATUSBAR_H
