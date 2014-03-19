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
    viewport.cpp \
    testobject.cpp \
    interaction.cpp \
    action.cpp \
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
    Managers/manager.cpp \
    Managers/objectmanager.cpp \
    Tools/tool.cpp \
    Tools/newpointtool.cpp \
    Tools/selectiontool.cpp \
    Tests/unittester.cpp \
    Tests/unittest.cpp \
    Attributes/transformationattributetest.cpp

HEADERS  += mainwindow.h \
    point.h \
    scene.h \
    viewport.h \
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
    Managers/manager.h \
    Managers/objectmanager.h \
    Tools/tool.h \
    Tools/newpointtool.h \
    Tools/selectiontool.h \
    Tests/unittester.h \
    Tests/unittest.h \
    Attributes/transformationattributetest.h


FORMS    += mainwindow.ui \
    AttributeWidgets/transformationwidget.ui \
    AttributeWidgets/stringwidget.ui \
    AttributeWidgets/typewidget.ui
