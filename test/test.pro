include(../defaults.pri)

TEMPLATE = app
# Add sql to test SQL features and add gui to test gui features
#	QT += core testlib sql gui
QT += core testlib sql gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = test
CONFIG +=console
CONFIG += app_bundle
INCLUDEPATH += .

LIBS += -L../src -lsubtle-cosmic-moose

SOURCES += \
    test_main.cpp
