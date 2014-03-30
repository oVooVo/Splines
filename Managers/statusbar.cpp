#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QStatusBar(parent)
{
    _messageLabel = new QLabel("", this);
    addWidget(_messageLabel);
}

void StatusBar::updateText()
{
    QString prefix = tr("Selected objects:");
    QString separator = ", ";
    QString selection;
    for (Object* o : scene()->selectedObjects())
        selection.append(
                    QString("%1%3")
                    .arg(o->name())
                    .arg(separator));

    if (selection.endsWith(separator)) {
        selection = selection.left(selection.length() - separator.length());
    }

    _messageLabel->setText(QString("%1 [%2]").arg(prefix, selection));

}
