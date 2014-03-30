#include "dockablemanager.h"
#include <QDebug>
#include <QMainWindow>

INIT_CREATOR_MAP(DockableManager);

DockableManager::DockableManager(QWidget *parent) : QDockWidget(parent)
{
}

DockableManager::~DockableManager()
{
    setScene(0);
}

void DockableManager::closeEvent(QCloseEvent *event)
{
    QDockWidget::closeEvent(event);
    deleteLater();
}
