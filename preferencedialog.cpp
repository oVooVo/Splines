#include "preferencedialog.h"
#include <QHBoxLayout>
#include <QScrollArea>
#include <AttributeWidgets/attributewidget.h>

PreferenceDialog::PreferenceDialog(QWidget *parent) :
    QDialog(parent)
{
    connect(this, SIGNAL(accepted()), this, SLOT(on_accept()));
    createUi();
}

PreferenceDialog::~PreferenceDialog()
{
}

void PreferenceDialog::createUi()
{
    _tabWidget = new QTabWidget(this);
    for (QString name : getTabNames()) {
        _tabWidget->addTab(createTabWidget(name, _tabWidget), name);
    }
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(_tabWidget);
    setLayout(layout);
}

QStringList PreferenceDialog::getTabNames()
{
    QStringList names;
    for (QString key : Preferences::keys()) {
        QString prefix = key.mid(0, key.indexOf('.'));
        if (!names.contains(prefix))
            names.append(prefix);
    }
    qSort(names);
    return names;
}

QWidget* PreferenceDialog::createTabWidget(QString name, QWidget* parent)
{
    QScrollArea* scrollArea = new QScrollArea(parent);
    QWidget* widget = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QStringList createdGroups;
    for (QString key : Preferences::keys()) {
        if (!key.startsWith(QString("%1.").arg(name))) continue;

        int afterFirstPoint = key.indexOf('.') + 1;
        int groupNameLength = key.indexOf('.', afterFirstPoint) - afterFirstPoint;
        QString groupTitle = key.mid(afterFirstPoint, groupNameLength);
        QString groupKey = key.mid(0, key.indexOf('.', afterFirstPoint));

        if (createdGroups.contains(groupKey)) continue;
        createdGroups << groupKey;
        QGroupBox* group = createGroupBox(groupKey, widget);
        group->setTitle(groupTitle);
        layout->addWidget(group);
    }
    widget->setLayout(layout);
    scrollArea->setWidget(widget);
    return scrollArea;
}

QGroupBox* PreferenceDialog::createGroupBox(QString pref, QWidget *parent)
{
    QGroupBox* box = new QGroupBox(parent);
    QHBoxLayout* layout = new QHBoxLayout(box);
    for (QString key : Preferences::keys()) {
        if (!key.startsWith(QString("%1.").arg(pref))) continue;

        QList<Attribute*> attributes;
        attributes << Preferences::attribute(key);

        QWidget* attributeWidget = AttributeWidget::createWidget(attributes);
        attributeWidget->setParent(box);
        layout->addWidget(attributeWidget);
    }
    box->setLayout(layout);
    return box;
}

void PreferenceDialog::on_accept()
{

}


















