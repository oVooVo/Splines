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
    Objects/spline.cpp \
    Objects/Spline/splinepiece.cpp \
    point.cpp \
    Objects/Spline/bezierpiece.cpp \
    scene.cpp \
    Objects/object.cpp \
    Objects/root.cpp \
    viewport.cpp \
    Managers/hierarchieexplorer.cpp \
    Managers/attributemanager.cpp \
    Attributes/transformationattribute.cpp \
    Attributes/attribute.cpp \
    AttributeWidgets/transformationwidget.cpp \
    Tests/unittester.cpp \
    Attributes/transformationattributetest.cpp \
    Tests/unittest.cpp \
    AttributeWidgets/attributewidget.cpp \
    Attributes/stringattribute.cpp \
    AttributeWidgets/stringwidget.cpp \
    testobject.cpp \
    Attributes/typeattribute.cpp \
    AttributeWidgets/typewidget.cpp \
    interaction.cpp \
    Tools/tool.cpp \
    Tools/newpointtool.cpp \
    Objects/pointobject.cpp \
    Tools/selectiontool.cpp

HEADERS  += mainwindow.h \
    Objects/spline.h \
    Objects/Spline/splinepiece.h \
    point.h \
    Objects/Spline/bezierpiece.h \
    scene.h \
    Objects/object.h \
    Objects/root.h \
    viewport.h \
    Managers/hierarchieexplorer.h \
    Managers/attributemanager.h \
    Attributes/transformationattribute.h \
    Attributes/attribute.h \
    AttributeWidgets/transformationwidget.h \
    Tests/unittester.h \
    Attributes/transformationattributetest.h \
    Tests/unittest.h \
    AttributeWidgets/attributewidget.h \
    Attributes/stringattribute.h \
    AttributeWidgets/stringwidget.h \
    testobject.h \
    Attributes/typeattribute.h \
    AttributeWidgets/typewidget.h \
    interaction.h \
    Tools/tool.h \
    Tools/newpointtool.h \
    Objects/pointobject.h \
    Tools/selectiontool.h

FORMS    += mainwindow.ui \
    AttributeWidgets/transformationwidget.ui \
    AttributeWidgets/stringwidget.ui \
    AttributeWidgets/typewidget.ui
