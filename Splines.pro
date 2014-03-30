#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T15:34:34
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Splines
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
    mainwindow.cpp \
    point.cpp \
    scene.cpp \
    Managers/viewport.cpp \
    testobject.cpp \
    interaction.cpp \
    Attributes/attribute.cpp \
    Attributes/stringattribute.cpp \
    Attributes/transformationattribute.cpp \
    Attributes/typeattribute.cpp \
    AttributeWidgets/attributewidget.cpp \
    AttributeWidgets/stringwidget.cpp \
    AttributeWidgets/transformationwidget.cpp \
    AttributeWidgets/typewidget.cpp \
    Objects/object.cpp \
    Objects/pointobject.cpp \
    Objects/spline.cpp \
    Objects/Spline/splinepiece.cpp \
    Objects/Spline/bezierpiece.cpp \
    Objects/root.cpp \
    Managers/attributemanager.cpp \
    Managers/objectmanager.cpp \
    Tools/tool.cpp \
    Tools/newpointtool.cpp \
    Tools/selectiontool.cpp \
    Tests/unittester.cpp \
    Tests/unittest.cpp \
    Attributes/transformationattributetest.cpp \
    Tools/selectalltool.cpp \
    Tools/deselectalltool.cpp \
    Tools/tangenttool.cpp \
    Objects/Spline/linearpiece.cpp \
    Dialogs/pointeditdialog.cpp \
    Attributes/boolattribute.cpp \
    AttributeWidgets/boolwidget.cpp \
    Objects/Spline/bpiece.cpp \
    Objects/Spline/cubicpiece.cpp \
    preferences.cpp \
    gradient.cpp \
    colorbutton.cpp \
    preferencedialog.cpp \
    Attributes/colorattribute.cpp \
    Attributes/doubleattribute.cpp \
    AttributeWidgets/colorwidget.cpp \
    AttributeWidgets/doublewidget.cpp \
    Tools/deletepointtool.cpp \
    undohandler.cpp \
    Managers/statusbar.cpp \
    Managers/dockablemanager.cpp \
    Managers/manager.cpp

HEADERS  += mainwindow.h \
    point.h \
    scene.h \
    Managers/viewport.h \
    testobject.h \
    interaction.h \
    action.h \
    Attributes/attribute.h \
    Attributes/stringattribute.h \
    Attributes/transformationattribute.h \
    Attributes/typeattribute.h \
    AttributeWidgets/attributewidget.h \
    AttributeWidgets/stringwidget.h \
    AttributeWidgets/transformationwidget.h \
    AttributeWidgets/typewidget.h \
    Objects/object.h \
    Objects/pointobject.h \
    Objects/spline.h \
    Objects/Spline/splinepiece.h \
    Objects/Spline/bezierpiece.h \
    Objects/root.h \
    Managers/attributemanager.h \
    Managers/objectmanager.h \
    Tools/tool.h \
    Tools/newpointtool.h \
    Tools/selectiontool.h \
    Tests/unittester.h \
    Tests/unittest.h \
    Attributes/transformationattributetest.h \
    register_defines.h \
    Tools/selectalltool.h \
    Tools/deselectalltool.h \
    Tools/tangenttool.h \
    Objects/Spline/linearpiece.h \
    Dialogs/pointeditdialog.h \
    Attributes/boolattribute.h \
    AttributeWidgets/boolwidget.h \
    Objects/Spline/bpiece.h \
    Objects/Spline/cubicpiece.h \
    preferences.h \
    gradient.h \
    colorbutton.h \
    preferencedialog.h \
    Attributes/colorattribute.h \
    Attributes/doubleattribute.h \
    AttributeWidgets/colorwidget.h \
    AttributeWidgets/doublewidget.h \
    Tools/deletepointtool.h \
    undohandler.h \
    Managers/statusbar.h \
    Managers/dockablemanager.h \
    Managers/manager.h


FORMS    += mainwindow.ui \
    AttributeWidgets/transformationwidget.ui \
    AttributeWidgets/stringwidget.ui \
    AttributeWidgets/typewidget.ui \
    Dialogs/pointeditdialog.ui \
    preferencedialog.ui \
    AttributeWidgets/colorwidget.ui \
    AttributeWidgets/doublewidget.ui
