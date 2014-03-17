#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T15:34:34
#
#-------------------------------------------------

QT       += core gui

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
    AttributeWidgets/transformationwidget.cpp

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
    AttributeWidgets/transformationwidget.h

FORMS    += mainwindow.ui \
    AttributeWidgets/transformationwidget.ui
